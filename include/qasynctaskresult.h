#ifndef QASYNCTASKRESULT_H
#define QASYNCTASKRESULT_H

#include <QString>

struct QAsyncTaskResult {
    bool success;
    QString message;
    void *userData;
};

#endif // QASYNCTASKRESULT_H
