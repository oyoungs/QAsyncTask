#include "qasynctaskcreator.h"
#include "qasynctaskreactor.h"
#include "qasynctask.h"
#include "qasynctaskevent.h"
#include "qasynctaskresponseevent.h"
#include <QCoreApplication>
#include <QDebug>

QAsyncTaskCreator::QAsyncTaskCreator(QAsyncTask *task, QObject *parent)
    : QObject(parent) ,_task(task)
{

}

void QAsyncTaskCreator::create(const QString &name, const QAsyncTaskArgs& args, const QAsyncTaskCallback &callback, int timeout, const QAsyncTaskTimeoutCallback &timeoutCb)
{
    _callbacks[name] = callback;
    if(_task) {
        QCoreApplication::postEvent(_task->reactor(), new QAsyncTaskEvent(name, args));
        qDebug() << "created async task";
    }
    if(timeout > 0 && timeoutCb) {
        int timer = startTimer(timeout);
        _timeout_timers.insert(name, timer);
        _timeout_callbacks.insert(timer, timeoutCb);
    }
}

bool QAsyncTaskCreator::event(QEvent *ev)
{
    if(ev->type() == (int)QAsyncTaskResponseEvent::EventType) {
        qDebug() << "received async task response";
        auto response = dynamic_cast<QAsyncTaskResponseEvent *>(ev);
        if(response && _callbacks.contains(response->name)) {
            auto callback = _callbacks[response->name];
            if(callback) {
                callback(response->result);
            }
            _callbacks.remove(response->name);
        }
        if(_timeout_timers.contains(response->name)) {
            auto timer = _timeout_timers[response->name];
            killTimer(timer);
            _timeout_callbacks.remove(timer);
            _timeout_timers.remove(response->name);
        }
    }
    return QObject::event(ev);
}

void QAsyncTaskCreator::timerEvent(QTimerEvent *event)
{
    int timer = event->timerId();
    if(_timeout_callbacks.contains(timer)) {
        qDebug() << "async task wait timeout";
        auto callback = _timeout_callbacks[timer];
        if(callback) {
            callback();
        }
        _timeout_callbacks.remove(timer);
        killTimer(timer);
    }
    QObject::timerEvent(event);
}
