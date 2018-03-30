#ifndef QASYNCTASK_H
#define QASYNCTASK_H

#include <QString>
#include <functional>

#include "qasynctaskresult.h"

class QAsyncTaskCreator;
class QAsyncTaskReactor;
class QAsyncTask
{
public:
    QAsyncTask();

    static QAsyncTask& global();

    void createTask(const QString& name, void *args, const std::function<void(const QAsyncTaskResult&)>& callback, int timeout = -1, const std::function<void()>& timeoutCb = nullptr);

    void registerTaskReactor(const QString& name, const std::function<QAsyncTaskResult(void *args)>& reactor);

    template<class T>
    void registerTaskReactor(const QString &name, QAsyncTaskResult (T::*func)(void *), T *obj) {
        registerTaskReactor(name, [func, obj](void *args)-> QAsyncTaskResult {
            return (static_cast<T *>(obj)->*func)(args);
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
