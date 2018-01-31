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

    QLabel *_lblPixmap;
    int _width;
    int _height;
    QPixmap _pixmap;
    Model *_model;

    MyPainter _myPainter;
    int _ticks;

    void RedrawPixmap();

    // Угол поворота в радианах
    float _rotateRadAngle;
    // Вектор оси поворота влево/вправо
    Vec3f _rotateVectLeftRight;
    // Вектор оси поворота вверх/вниз
    Vec3f _rotateVectUpDown;

private slots:
    //Слот для обновления
    void updateImage();

    void OnPressLeft();
    void OnPressRight();
    void OnPressUp();
    void OnPressDown();
};

#endif // MAINWINDOW_H
