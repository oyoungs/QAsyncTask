

#include "mainwindow.h"
#include "qasynctask.h"

#include <QUrl>
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.load([&] {
        QAsyncTask::global().createTask("load", {
                {"url", w.url().toStdString() }
        }, [&] (const QAsyncTaskResult& result ) {
            if(result.success) {
                w.setPicture(result.message);
            } else {
                w.setText(result.message);
            }
        });
    });

    QAsyncTask::global().registerTaskReactor("load", [](const QAsyncTaskArgs& args) {

        auto url = args.value("url", "http://127.0.0.1");
        auto qUrl = QUrl(url.c_str());

        if(!qUrl.isValid()) {
            return QAsyncTaskResult {
                    false, "图片地址不对"
            };
        }



        auto path = QString("%1/%2").arg(getenv("PWD")).arg(qUrl.fileName());


        std::system(QString("curl -o %1 %2").arg(path).arg(url.c_str()).toStdString().c_str());


        return QAsyncTaskResult {
                true, path
        };
    });

    QPoint position = a.desktop()->screenGeometry().center();

    position.setX(position.x() - w.width() / 2);
    position.setY(position.y() - w.height() / 2);

    w.move(position);

    w.show();

    return a.exec();
}
