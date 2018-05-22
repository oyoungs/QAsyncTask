#include "qasynctask.h"
#include "qasynctaskcreator.h"
#include "qasynctaskreactor.h"

QAsyncTask::QAsyncTask()
    : _creator(new QAsyncTaskCreator(this))
    , _reactor(new QAsyncTaskReactor(this))
{

}

void QAsyncTask::createTask(const QString &name, const QAsyncTaskArgs& args, const ResultHandle &callback, int timeout, const TimeoutHandle& timeoutCb)
{
    _creator->create(name, args, callback, timeout, timeoutCb);
}


void QAsyncTask::registerTaskReactor(const QString &name, const ReactorHandle &reactor)
{
    _reactor->registerReactorHandler(name, reactor);
}


QAsyncTask::~QAsyncTask()
{
    delete _creator;
    delete _reactor;
}


QAsyncTask& QAsyncTask::global()
{
    static QAsyncTask task;
    return task;
}
