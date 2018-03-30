#include "qasynctask.h"
#include "qasynctaskcreator.h"
#include "qasynctaskreactor.h"

QAsyncTask::QAsyncTask()
    : _creator(new QAsyncTaskCreator(this))
    , _reactor(new QAsyncTaskReactor(this))
{

}

void QAsyncTask::createTask(const QString &name, void *args, const std::function<void (const QAsyncTaskResult &)> &callback, int timeout, const std::function<void()>& timeoutCb)
{
    _creator->create(name, args, callback, timeout, timeoutCb);
}


void QAsyncTask::registerTaskReactor(const QString &name, const std::function<QAsyncTaskResult (void *)> &reactor)
{
    _reactor->registerReactorHandler(name, reactor);
}

void QAsyncTask::setTimeout(int timeout, const std::function<void()>& func)
{
  _creator->setTimeout(timeout, func);
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
