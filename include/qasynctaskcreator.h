#ifndef QASYNCTASKCREATOR_H
#define QASYNCTASKCREATOR_H

#include <QMap>
#include <QObject>
#include "qasynctaskresult.h"

#include <functional>

class QAsyncTask;
class QAsyncTaskCreator : public QObject
{
    Q_OBJECT
public:
    typedef std::function<void (const QAsyncTaskResult &)> QAsyncTaskCallback;
    typedef std::function<void()> QAsyncTaskTimeoutCallback;
    explicit QAsyncTaskCreator(QAsyncTask *task, QObject *parent = 0);

    void create(const QString &name, void *args, const QAsyncTaskCallback &callback, int timeout = -1, const QAsyncTaskTimeoutCallback& timeoutCb = nullptr);

protected:
    bool event(QEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    QAsyncTask *_task;
    QMap<QString, QAsyncTaskCallback> _callbacks;
    QMap<int, QAsyncTaskTimeoutCallback> _timeout_callbacks;
};

#endif // QASYNCTASKCREATOR_H
