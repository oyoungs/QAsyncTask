#include "qasynctaskcreator.h"
#include "qasynctaskreactor.h"
#include "qasynctask.h"
#include "qasynctaskevent.h"
#include "qasynctaskresponseevent.h"
#include <QCoreApplication>

QAsyncTaskCreator::QAsyncTaskCreator(QAsyncTask *task, QObject *parent)
    : QObject(parent) ,_task(task)
{

}

void QAsyncTaskCreator::create(const QString &name, void *args, const QAsyncTaskCallback &callback, int timeout, const QAsyncTaskTimeoutCallback &timeoutCb)
{
    _callbacks[name] = callback;
    if(_task) {
        QCoreApplication::postEvent(_task->reactor(), new QAsyncTaskEvent(name, args));
    }
    if(timeout > 0 && timeoutCb) {
        int timer = startTimer(timeout);
        _timeout_callbacks[timer] = timeoutCb;
    }
}

bool QAsyncTaskCreator::event(QEvent *ev)
{
    if(ev->type() == QAsyncTaskResponseEvent::EventType) {
        auto response = dynamic_cast<QAsyncTaskResponseEvent *>(ev);
        if(response && _callbacks.contains(response->name)) {
            auto callback = _callbacks[response->name];
            if(callback) {
                callback(response->result);
            }
            _callbacks.remove(response->name);
        }
    }
    return QObject::event(ev);
}

void QAsyncTaskCreator::timerEvent(QTimerEvent *event)
{
    int timer = event->timerId();
    if(_timeout_callbacks.contains(timer)) {
        auto callback = _timeout_callbacks[timer];
        if(callback) {
            callback();
            _timeout_callbacks.remove(timer);
        }
    }
    killTimer(timer);
    QObject::timerEvent(event);
}
