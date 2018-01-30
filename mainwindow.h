#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QAction>
#include <QLabel>
#include <QPixmap>

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
    QPixmap _pixmap;

private slots:
    //Слот для обновления
    void updateImage();

    void OnPressLeft();
    void OnPressRight();
    void OnPressUp();
    void OnPressDown();
};

#endif // MAINWINDOW_H
