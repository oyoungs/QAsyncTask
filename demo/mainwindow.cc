#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


QString MainWindow::url() const {
    return QString("http://%1").arg(ui->textUrl->text());
}

void MainWindow::setText(const QString& text)
{
    ui->lblImage->setText(text);
    ui->lblImage->setPixmap(QPixmap::fromImage(QImage()));
}

void MainWindow::setPicture(const QString& file)
{
    ui->lblImage->setText("");
    ui->lblImage->setPixmap(QPixmap::fromImage(QImage(file)));
}

void MainWindow::on_btLoad_clicked()
{
    if(mfunc) mfunc();

}
