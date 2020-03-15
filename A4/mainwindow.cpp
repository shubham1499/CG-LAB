#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QApplication>
#include<QtGui>
#include<QColorDialog>
QImage image(300,300,QImage::Format_RGB888);
QColor col;
QRgb color;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start=true;
    j=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if(start==true)
    {
        int p=ev->pos().x();
        int q=ev->pos().y();
        a[j]=p;
        b[j]=q;



        if(ev->button()==Qt::RightButton)
        {
            dda(a[0],b[0],a[j-1],b[j-1]);
            start=false;
        }
        else if(j>0)
        {
            dda(a[j],b[j],a[j-1],b[j-1]);
        }
    j++;}

}

void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    float x,y;

    QRgb value;
    value=col.rgb();
    float len;
    len=(abs(x2-x1)>abs(y2-y1)?abs(x2-x1):abs(y2-y1));
    float dy=(y2-y1)/len;
    float dx=(x2-x1)/len;
     x=x1+(0.5*sign(x2,x1));
    y=y1+(0.5*sign(y2,y1));

    int i=1;

    while(i<=len)
    {
        image.setPixel(int(x),int(y),value);
        x=x+dx;
        y=y+dy;

        ui->label->setPixmap(QPixmap::fromImage(image));

        i++;
    } image.setPixel(int(x),int(y),value);

}

int MainWindow::sign(float a2,float a1)
{
    float z;
    z=a2-a1;

    if(z>0)
    {
        return 1;
    }
    else if(z<0)
    {
        return -1;
    }
    else
    {
        return 0;
    }

}

void MainWindow::on_pushButton_clicked()
{
    col=QColorDialog::getColor();
}

