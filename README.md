# QAsyncTask
## A tool for execute some async task and do the callback in the main thread(UI thread)

## usage:
1. include the header file qasynctask.h
2. add library libqasync to the project, eg. -lqasync
3. sample code 

```cpp

#include "qasynctask.h"
#include <QApplication>
#include <thread>
#include <iostream>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    
    QAsyncTask task;
    task.registerTaskReactor("test", [](void *args) {
        QAsyncTaskResult result;
        result.success = true;
        result.message = "Success";
        result.userData = args;
        return result;
    });

    task.createTask("test", nullptr, [](const QAsyncTaskResult& result) {
        std::cout  << (result.success ? "successful": "failed") << std::endl;
        std::cout << "callback thread: " << std::this_thread::get_id() << std::endl;
    });

    std::cout << "main thread: " << std::this_thread::get_id() << std::endl ;

    return a.exec();
}

```

