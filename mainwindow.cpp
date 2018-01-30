#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _updateTimer = new QTimer(this);
    // Период таймера = 1000 / 60 Гц = 16.667 мс
    _updateTimer->setInterval(1000/60);
    connect(_updateTimer, &QTimer::timeout, this, &MainWindow::updateImage);

    // Запуск таймера
    _updateTimer->start();

    // Нажатие на кнопки стрелок
    _actLeft = new QAction(this);
    _actRight = new QAction(this);
    _actUp = new QAction(this);
    _actDown = new QAction(this);

    connect(_actLeft, &QAction::triggered, this, &MainWindow::OnPressLeft);
    connect(_actRight, &QAction::triggered, this, &MainWindow::OnPressRight);
    connect(_actUp, &QAction::triggered, this, &MainWindow::OnPressUp);
    connect(_actDown, &QAction::triggered, this, &MainWindow::OnPressDown);

    _actUp->setShortcut(QKeySequence("W"));
    _actLeft->setShortcut(QKeySequence("A"));
    _actDown->setShortcut(QKeySequence("S"));
    _actRight->setShortcut(QKeySequence("D"));

    addAction(_actLeft);
    addAction(_actRight);
    addAction(_actUp);
    addAction(_actDown);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateImage()
{
    //qDebug() << "WAAAAGH!";
}

void MainWindow::OnPressLeft()
{
    qDebug() << "OnPressLeft";
}

void MainWindow::OnPressRight()
{
    qDebug() << "OnPressRight";
}

void MainWindow::OnPressUp()
{
    qDebug() << "OnPressUp";
}

void MainWindow::OnPressDown()
{
    qDebug() << "OnPressDown";
}
