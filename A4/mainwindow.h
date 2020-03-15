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
    void mousePressEvent(QMouseEvent *ev);
    void dda(float,float,float,float);
    int sign(float,float);


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool start;
    int j;
    int a[10];
    int b[10];
};

#endif // MAINWINDOW_H
