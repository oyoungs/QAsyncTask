#ifndef QASYNCTASKEVENT_H
#define QASYNCTASKEVENT_H

#include <QEvent>
#include <QString>
#include "qasynctaskargs.h"

class QAsyncTaskEvent : public QEvent
{
public:

    enum {
        EventType = QEvent::User + 1000
    };

    QAsyncTaskEvent(const QString& name, const QAsyncTaskArgs& args);

    QString name;
    QAsyncTaskArgs args;

};

#endif // QASYNCTASKEVENT_H
