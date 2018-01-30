#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateTimer = new QTimer(this);
    // Период таймера = 1000 / 60 Гц = 16.667 мс
    updateTimer->setInterval(1000/60);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateImage);

    // Запуск таймера
    updateTimer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateImage()
{
    qDebug() << "WAAAAGH!";
}
