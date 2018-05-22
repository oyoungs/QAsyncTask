#ifndef QASYNCTASK_H
#define QASYNCTASK_H

#include <QString>
#include <functional>


#include "qasynctaskargs.h"
#include "qasynctaskresult.h"

class QAsyncTaskCreator;
class QAsyncTaskReactor;
class QAsyncTask
{
public:
    QAsyncTask();

    typedef std::function<QAsyncTaskResult(const QAsyncTaskArgs&)> ReactorHandle;
    typedef std::function<void(const QAsyncTaskResult&)> ResultHandle;
    typedef std::function<void()> TimeoutHandle;

    static QAsyncTask& global();

    void createTask(const QString& name, const QAsyncTaskArgs& args, const ResultHandle& callback, int timeout = -1, const TimeoutHandle& timeoutCb = nullptr);

    void registerTaskReactor(const QString& name, const ReactorHandle& reactor);

    template<class T, QAsyncTaskResult (T::*func)(const QAsyncTaskArgs&)>
    void registerTaskReactor(const QString &name, T *obj) {
        registerTaskReactor(name, [=](const QAsyncTaskArgs& args)-> QAsyncTaskResult {
            return (obj->*func)(args);
        });
    }

    QAsyncTaskCreator *creator() {
        return _creator;
    }

    QAsyncTaskReactor *reactor() {
        return _reactor;
    }

    ~QAsyncTask();


private:
    QAsyncTaskCreator *_creator;
    QAsyncTaskReactor *_reactor;
};

#endif // QASYNCTASK_H
