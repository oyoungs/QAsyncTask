#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <functional>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    template<typename Func, typename ...Args>
    void load(Func&& func, Args&& ...args) {
        mfunc = std::bind(func, std::forward<Args>(args)...);
    }

    QString url() const;

    void setText(const QString& text);
    void setPicture(const QString& file);

    ~MainWindow();
private slots:
    void on_btLoad_clicked();

private:
    Ui::MainWindow *ui;

    std::function<void()> mfunc;
};

#endif // MAINWINDOW_H
