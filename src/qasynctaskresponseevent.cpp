#include "qasynctaskresponseevent.h"

QAsyncTaskResponseEvent::QAsyncTaskResponseEvent(const QString &name, const QAsyncTaskResult &r)
    : QEvent((QEvent::Type)(QEvent::User + 1001)), name(name), result(r)
{

}
