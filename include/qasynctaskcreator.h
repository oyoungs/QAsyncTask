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
    explicit QAsyncTaskCreator(QAsyncTask *task, QObject *parent = 0);

    void create(const QString &name, void *args, const QAsyncTaskCallback &callback);

protected:
    bool event(QEvent *event) override;

private:
    QAsyncTask *_task;
    QMap<QString, QAsyncTaskCallback> _callbacks;
};

#endif // QASYNCTASKCREATOR_H
