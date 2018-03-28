#ifndef QASYNCTASKRESPONSEEVENT_H
#define QASYNCTASKRESPONSEEVENT_H

#include <QEvent>
#include "qasynctaskresult.h"

class QAsyncTaskResponseEvent : public QEvent
{
public:
    QAsyncTaskResponseEvent(const QString& name, const QAsyncTaskResult& r);
    QString name;
    QAsyncTaskResult result;
};

#endif // QASYNCTASKRESPONSEEVENT_H
