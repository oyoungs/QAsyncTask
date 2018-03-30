#include "qasynctaskevent.h"

QAsyncTaskEvent::QAsyncTaskEvent(const QString &name, void *args)
    : QEvent((QEvent::Type)(EventType)), name(name), args(args)
{
}
