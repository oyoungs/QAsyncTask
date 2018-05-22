#include "qasynctaskevent.h"

QAsyncTaskEvent::QAsyncTaskEvent(const QString &name, const QAsyncTaskArgs &args)
    : QEvent((QEvent::Type)(EventType)), name(name), args(args)
{

}
