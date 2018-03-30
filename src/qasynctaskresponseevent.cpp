#include "qasynctaskresponseevent.h"

QAsyncTaskResponseEvent::QAsyncTaskResponseEvent(const QString &name, const QAsyncTaskResult &r)
    : QEvent((QEvent::Type)(EventType)), name(name), result(r)
{

}
