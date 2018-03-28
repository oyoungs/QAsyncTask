#ifndef QASYNCTASKEVENT_H
#define QASYNCTASKEVENT_H

#include <QEvent>
#include <QString>

class QAsyncTaskEvent : public QEvent
{
public:
    QAsyncTaskEvent(const QString& name, void *args);

    QString name;
    void *args;

};

#endif // QASYNCTASKEVENT_H
