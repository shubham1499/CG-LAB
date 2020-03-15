#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    float x[12], y[12];
    void draw();
    void bresenham(float, float, float, float);
    int sign(float a);
    void matmul(float a[4][3], float b[3][3]);
    void seedfill(float x, float y);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Draw_button_clicked();

    void on_rotateButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
