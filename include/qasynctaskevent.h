#ifndef QASYNCTASKEVENT_H
#define QASYNCTASKEVENT_H

#include <QEvent>
#include <QString>

class QAsyncTaskEvent : public QEvent
{
public:

    enum {
        EventType = QEvent::User + 1000
    };

    QAsyncTaskEvent(const QString& name, void *args);

    QString name;
    void *args;

};

#endif // QASYNCTASKEVENT_H
