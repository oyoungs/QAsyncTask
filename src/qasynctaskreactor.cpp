#include "qasynctaskreactor.h"
#include "qasynctaskcreator.h"
#include "qasynctaskevent.h"
#include "qasynctaskresponseevent.h"
#include "qasynctask.h"

#include <QCoreApplication>
#include <future>

QAsyncTaskReactor::QAsyncTaskReactor(QAsyncTask *task, QObject *parent)
    : QObject(parent), _task(task)
{

}

bool QAsyncTaskReactor::event(QEvent *ev)
{
    if(ev->type() != QAsyncTaskEvent::EventType) return false;
    auto taskEvent = (QAsyncTaskEvent *)ev;
    auto name = taskEvent->name;
    auto args = taskEvent->args;
    if(_handlers.contains(name)) {
        auto handler = _handlers[name];
        if(handler && _task) {
            std::async(std::launch::async,[this, handler, name, args]{
                auto result = handler(args);
                QCoreApplication::postEvent(_task->creator(), new QAsyncTaskResponseEvent(name, result));
            });
        }
    }
    return QObject::event(ev);
}


void QAsyncTaskReactor::registerReactorHandler(const QString &name, const Handler &handler)
{
    _handlers[name] = handler;
}
