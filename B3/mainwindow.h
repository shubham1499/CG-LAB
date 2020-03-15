#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void displayLine(float,float,float,float);
    void mousePressEvent(QMouseEvent *event);
    void cohenSutherlandClip(float,float,float,float);
    int  computeCode(float,float);

    float abs_x,abs_y,del_x,del_y,len;
    bool marker;
    float a[2],b[2];
    int flag,x_min,x_max,y_min,y_max;
    int INSIDE;
    int UP;
    int BELOW;
    int RIGHT;
    int LEFT;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
