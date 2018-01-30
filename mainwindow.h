#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
    QTimer *updateTimer;

private slots:
    //Слот для обновления
    void updateImage();
};

#endif // MAINWINDOW_H
