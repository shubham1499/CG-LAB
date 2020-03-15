#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initial()
{
    x1=ui->plainTextEdit_3->toPlainText().toFloat();
    y1=ui->plainTextEdit->toPlainText().toFloat();
    x2=ui->plainTextEdit_4->toPlainText().toFloat();
    y2=ui->plainTextEdit_2->toPlainText().toFloat();
    abs_x= x2>x1?(x2-x1):(x1-x2);
    abs_y= y2>y1?(y2-y1):(y1-y2);
    len = abs_x>abs_y?abs_x:abs_y;
    del_x=(x2-x1)/len;
    del_y=(y2-y1)/len;

}
QImage image(300,300, QImage::Format_RGB888);
void MainWindow::on_pushButton_clicked()
{
    initial();

    float x=x1+(0.5*(x2>x1?1:(x2<x1)?(-1):0));
    float y=y1+(0.5*(y2>y1?1:(y2<y1)?(-1):0));
    int i=1;
    QRgb value;
    value=qRgb(255,255,255);   //set color of pixel as green
    while(i<=len)
    {
        image.setPixel(int(x),int(y),value);
        x = x+del_x;
        y = y+del_y;
         //draws pixel with value
        i++;
    }

     ui->label_5->setPixmap(QPixmap::fromImage(image));


}
void MainWindow::on_pushButton_2_clicked()
{
    initial();
    float temp;
    int interchange;
    float x=x1;
    float y=y1;
    float delx=(x2>x1)?(x2-x1):(x1-x2);
    float dely=(y2>y1)?(y2-y1):(y1-y2);
    int s1=(x2>x1?1:(x2<x1)?(-1):0);
    int s2=(y2>y1?1:(y2<y1)?(-1):0);
    float e=(2*(dely))-delx;
    if(dely>delx)
    {
         temp=delx;
         delx=dely;
         dely=temp;
         interchange=1;
    }
    else
    {
        interchange=0;
    }
    QRgb value1;
    value1=qRgb(255,0,0);
    for(int i=1;i<=delx;i++)
    {
         image.setPixel(int(x),int(y),value1);
         while(e>=0)
         {
             if(interchange==1)
             {
                 x=x+s1;
             }
             else
                 y=y+s2;
             e=e-(2*(delx));
         }
         if(interchange==1)
         {
             y=y+s2;
         }
         else
         {
             x=x+s1;
         }
         e=e+(2*dely);

    }
     ui->label_5->setPixmap(QPixmap::fromImage(image));
}
