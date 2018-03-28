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

bool QAsyncTaskReactor::event(QEvent *event)
{
    auto taskEvent = (QAsyncTaskEvent *)event;
    auto name = taskEvent->name;
    auto args = taskEvent->args;
    auto handler = _handlers[name];
    if(handler && _task) {
        std::async(std::launch::async,[this, handler, name, args]{
            auto result = handler(args);
            QCoreApplication::postEvent(_task->creator(), new QAsyncTaskResponseEvent(name, result));
        });

    }
    return true;
}


void QAsyncTaskReactor::registerReactorHandler(const QString &name, const Handler &handler)
{
    _handlers[name] = handler;
}
