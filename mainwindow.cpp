#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _ticks(0)
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


    // Label на который будет рисоваться _pixmap;
    _lblPixmap = new QLabel("TEST");
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(_lblPixmap);
    this->centralWidget()->setLayout(layout);

    // Начальное изображение
    _width = 640;
    _height = 512;
    _pixmap = QPixmap(_width, _height);

    // Чтение модели
    const char *filename = "obj/african_head.obj";
    if(QFile::exists(filename))
    {
        qDebug() << "read model:" << filename;
        _model = new Model(filename);
        _myPainter.SetModel(_model);
    }
    else
    {
        qDebug() << "file not exist" << filename;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _model;
}

void MainWindow::updateImage()
{
    _ticks++;
    RedrawPixmap();
    //qDebug() << "WAAAAGH!";

    // Вывод получившегося изображения
    QPixmap local = _pixmap;
    _lblPixmap->setPixmap(local);
}

void MainWindow::RedrawPixmap()
{
    // ToDo Для теста, изменение цвета каждый тик
    QImage local(_width, _height, QImage::Format_ARGB32);
    QColor color;
    color.setRed(_ticks % 255);
    local.fill(color);

    // Получение указателя на данные изображения
    auto ptrData = local.scanLine(0);
    auto pixs = (Pixel*)ptrData;

    _myPainter.DrawCube(pixs, local.width(), local.height());

    _pixmap = QPixmap::fromImage(local);
}

void MainWindow::OnPressLeft()
{
    qDebug() << "OnPressLeft";
    // ToDo поменять какой-нибудь коээфициент, который будет учавствовать в перерисовке
    RedrawPixmap();
}

void MainWindow::OnPressRight()
{
    qDebug() << "OnPressRight";
    // ToDo поменять какой-нибудь коээфициент, который будет учавствовать в перерисовке
    RedrawPixmap();
}

void MainWindow::OnPressUp()
{
    qDebug() << "OnPressUp";
    // ToDo поменять какой-нибудь коээфициент, который будет учавствовать в перерисовке
    RedrawPixmap();
}

void MainWindow::OnPressDown()
{
    qDebug() << "OnPressDown";
    // ToDo поменять какой-нибудь коээфициент, который будет учавствовать в перерисовке
    RedrawPixmap();
}

