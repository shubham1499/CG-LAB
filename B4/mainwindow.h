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
    ~MainWindow();
    void dda(int x1,int y1,int x2,int y2);
    int sign(int);
    void x_reflect(int x1,int y1,int x2,int y2);
    void y_reflect(int x1,int y1,int x2,int y2);
    void xy_reflect(float x1,float y1,float x2,float y2);
    void multiply(int v[2][3],float m[3][3]);
    void arbitrary_rotate(float x1, float y1, float x2, float y2, float x3, float y3, float angle);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
