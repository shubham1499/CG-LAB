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
    explicit MainWindow(QWidget *parent = 0);
    int sign(float,float);
    void bresenham(float,float,float,float);
    void bresenham1(float,float,float,float);
    void draw();
    void seedfill(float,float);
    void seedfill1(float,float);
    void calculate(float);

    void multiply(float arr[10][10],float rot[10][10]);
    void matrix1(float,float,float,float);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::MainWindow *ui;
    float a1,b1,a2,b2,a3,b3,a4,b4;
    float arr[10][10],rot[10][10],result[10][10];
    int width,height;
    int c1,c2,g1,side;
};

#endif // MAINWINDOW_H
