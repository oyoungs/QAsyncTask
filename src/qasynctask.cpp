#include "qasynctask.h"
#include "qasynctaskcreator.h"
#include "qasynctaskreactor.h"

QAsyncTask::QAsyncTask()
    : _creator(new QAsyncTaskCreator(this))
    , _reactor(new QAsyncTaskReactor(this))
{

}

void QAsyncTask::createTask(const QString &name, void *args, const std::function<void (const QAsyncTaskResult &)> &callback)
{
    _creator->create(name, args, callback);
}


void QAsyncTask::registerTaskReactor(const QString &name, const std::function<QAsyncTaskResult (void *)> &reactor)
{
    _reactor->registerReactorHandler(name, reactor);
}
