#include "qasynctaskevent.h"

QAsyncTaskEvent::QAsyncTaskEvent(const QString &name, void *args)
    : QEvent((QEvent::Type)(QEvent::User + 1000)), name(name), args(args)
{
}
