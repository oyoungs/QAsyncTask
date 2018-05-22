#include "qasynctaskreactor.h"
#include "qasynctaskcreator.h"
#include "qasynctaskevent.h"
#include "qasynctaskresponseevent.h"
#include "qasynctask.h"

#include <thread>

#include <QCoreApplication>
#include <QDebug>

QAsyncTaskReactor::QAsyncTaskReactor(QAsyncTask *task, QObject *parent)
    : QObject(parent), _task(task)
{

}

bool QAsyncTaskReactor::event(QEvent *ev)
{
    if(ev->type() == (int)QAsyncTaskEvent::EventType) {
        qDebug() << "received async task request";
        auto taskEvent = dynamic_cast<QAsyncTaskEvent *>(ev);
        auto name = taskEvent->name;
        auto args = taskEvent->args;
        qDebug() << "async task name:" << name;
        if(_handlers.contains(name)) {
            auto handler = _handlers[name];
            if(handler && _task) {
                qDebug() << "async task [" << name <<"] will execute";
                std::thread([=]{
                    qDebug() << "handler will proccess";
                    auto result = handler(args);
                    qDebug() << "async task handler process finish, result: " << result.success;
                    QCoreApplication::postEvent(_task->creator(), new QAsyncTaskResponseEvent(name, result));
                }).detach();
            }
        }
    }
    return QObject::event(ev);
}


void QAsyncTaskReactor::registerReactorHandler(const QString &name, const ReactorHandler &handler)
{
    _handlers[name] = handler;
}

QAsyncTaskReactor::~QAsyncTaskReactor()
{

}
