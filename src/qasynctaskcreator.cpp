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

void QAsyncTaskCreator::create(const QString &name, void *args, const QAsyncTaskCallback &callback)
{
    _callbacks[name] = callback;
    if(_task) {
        QCoreApplication::postEvent(_task->reactor(), new QAsyncTaskEvent(name, args));
    }
}

bool QAsyncTaskCreator::event(QEvent *event)
{
    auto response = (QAsyncTaskResponseEvent *)event;
    auto callback = _callbacks[response->name];
    if(callback) {
        callback(response->result);
    }
    return true;
}
