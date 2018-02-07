#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QAction>
#include <QLabel>
#include <QPixmap>

#include "MyPainter.h"
#include "model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Таймер для установки отображаемого изображения
    QTimer *_updateTimer;

    QAction *_actLeft;
    QAction *_actRight;
    QAction *_actUp;
    QAction *_actDown;
    // Действие для смены режима отрисовки
    QAction *_actChangeDrawType;

    QLabel *_lblPixmap;
    int _width;
    int _height;
    QPixmap _pixmap;
    Model *_model;

    MyPainter _myPainter;
    DrawType _drawType;
    int _ticks;

    void RedrawPixmap();

    // Угол поворота в радианах
    float _rotateRadAngle;
    // Вектор оси поворота влево/вправо
    Vec3f _rotateVectLeftRight;
    // Вектор оси поворота вверх/вниз
    Vec3f _rotateVectUpDown;

    void RotateModel(Matrix3x3<float> &mRotate);

private slots:
    //Слот для обновления
    void updateImage();

    void OnPressLeft();
    void OnPressRight();
    void OnPressUp();
    void OnPressDown();

    void OnDrawTypeChanged();
};

#endif // MAINWINDOW_H
