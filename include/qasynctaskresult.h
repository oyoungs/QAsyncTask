#ifndef QASYNCTASKRESULT_H
#define QASYNCTASKRESULT_H

#include <QString>
#include "qasynctaskargs.h"

struct QAsyncTaskResult {
    bool success;
    QString message;
    QAsyncTaskArgs userData;
};

#endif // QASYNCTASKRESULT_H
