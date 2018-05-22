

#include "qasynctask.h"

#include <thread>
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QAsyncTask task;
    QApplication a(argc, argv);

    task.registerTaskReactor("test", [](const QAsyncTaskArgs& rgs) {
        QAsyncTaskResult result;
        result.success = true;
        result.message = "Success";
        result.userData = nullptr;
        return result;
    });

    task.createTask("test", QAsyncTaskArgs{}, [](const QAsyncTaskResult& result) {
        std::cout  << (result.success ? "successful": "failed") << std::endl;
        std::cout << "callback thread:" << std::this_thread::get_id() << std::endl;
    });

    std::cout << "main thread:" << std::this_thread::get_id() << std::endl ;

    return a.exec();
}
