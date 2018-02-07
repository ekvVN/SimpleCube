#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _ticks(0),
    _rotateVectLeftRight(0.0f, 1.0f, 0.0f),
    _rotateVectUpDown(1.0f, 0.0f, 0.0f),
    _rotateRadAngle(0.05f),
    _model(nullptr),
    _drawType(DrawType_Wireframe)
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
    // Действие для смены режима отрисовки
    _actChangeDrawType = new QAction(this);

    connect(_actLeft, &QAction::triggered, this, &MainWindow::OnPressLeft);
    connect(_actRight, &QAction::triggered, this, &MainWindow::OnPressRight);
    connect(_actUp, &QAction::triggered, this, &MainWindow::OnPressUp);
    connect(_actDown, &QAction::triggered, this, &MainWindow::OnPressDown);
    connect(_actChangeDrawType, &QAction::triggered, this, &MainWindow::OnDrawTypeChanged);

    _actUp->setShortcut(QKeySequence("W"));
    _actLeft->setShortcut(QKeySequence("A"));
    _actDown->setShortcut(QKeySequence("S"));
    _actRight->setShortcut(QKeySequence("D"));
    _actChangeDrawType->setShortcut(QKeySequence("Q"));

    addAction(_actLeft);
    addAction(_actRight);
    addAction(_actUp);
    addAction(_actDown);
    addAction(_actChangeDrawType);


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
//    const char *filename = "obj/empty";
    const char *filename = "obj/african_head.obj";
//    const char *filename = "obj/Cube.obj";
//    const char *filename = "obj/cube.obj";
//    const char *filename = "obj/cube2.obj";
//    const char *filename = "obj/CubeMy.obj";
//    const char *filename = "obj/CubeMy3.obj";
//    const char *filename = "obj/CubeMy4.obj";
//    const char *filename = "obj/Cylinder.obj";
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

    // Установка направления света
    _myPainter.setLightDir(Vec3f(0, 0, 1));

    // Установка матрицы просмотра/вьюпорта/камеры
    auto viewMatrix = std::make_shared<ViewMatrix>();
    viewMatrix->width = _width;
    viewMatrix->height = _height;
    viewMatrix->eye = {0, 0, 1};
    viewMatrix->center = {0, 0, 0};
    viewMatrix->up = {0, 1, 0};
    viewMatrix->calcViewMatrix();

    _myPainter._viewMatrix = viewMatrix;
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
    QColor color(0,0,0);
//    color.setRed(_ticks % 255);
    local.fill(color);

    // Получение указателя на данные изображения
    auto ptrData = local.scanLine(0);
    auto pixs = (Pixel*)ptrData;

    _myPainter.DrawCube(pixs, local.width(), local.height());

    _pixmap = QPixmap::fromImage(local);
}

void MainWindow::RotateModel(Matrix3x3<float> &mRotate)
{
    if(!_model)
        return;

    _model->apply(mRotate);
    RedrawPixmap();
}

void MainWindow::OnPressLeft()
{
    auto mRotate = GetRotateMatrix(_rotateVectLeftRight, _rotateRadAngle);
    RotateModel(mRotate);
}

void MainWindow::OnPressRight()
{
    auto mRotate = GetRotateMatrix(_rotateVectLeftRight, -_rotateRadAngle);
    RotateModel(mRotate);
}

void MainWindow::OnPressUp()
{
    auto mRotate = GetRotateMatrix(_rotateVectUpDown, _rotateRadAngle);
    RotateModel(mRotate);
}

void MainWindow::OnPressDown()
{
    auto mRotate = GetRotateMatrix(_rotateVectUpDown, -_rotateRadAngle);
    RotateModel(mRotate);
}

void MainWindow::OnDrawTypeChanged()
{
    auto newValue = (_drawType + 1) % DrawType_EndIdx;
    _drawType = static_cast<DrawType>(newValue);
    _myPainter.setDrawType(_drawType);
}

