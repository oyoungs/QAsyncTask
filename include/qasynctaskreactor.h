#ifndef QASYNCTASKREACTOR_H
#define QASYNCTASKREACTOR_H

#include <QMap>
#include <QList>
#include <QObject>

#include "qasynctaskresult.h"
#include <functional>

class QAsyncTask;
class QAsyncTaskReactor : public QObject
{
    Q_OBJECT
public:
    typedef std::function<QAsyncTaskResult(void *args)> Handler;
    explicit QAsyncTaskReactor(QAsyncTask* task, QObject *parent = 0);

    void registerReactorHandler(const QString& name, const Handler& handler);

protected:
    bool event(QEvent *event) override;

private:
    QAsyncTask *_task;
    QMap<QString, Handler > _handlers;
};

#endif // QASYNCTASKREACTOR_H
