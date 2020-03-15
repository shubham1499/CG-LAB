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
     int x,y;
private slots:
    void on_pushButton_clicked();

    int sign(int);

    void BresenhamLineDrawingAlgo(int x1 , int y1 , int x2 , int y2);

    void Hilbert(int level);

    void HilbertA(int level);

    void HilbertB(int level);

    void HilbertC(int level);

    void HilbertD(int level);

    void line(int , int);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
