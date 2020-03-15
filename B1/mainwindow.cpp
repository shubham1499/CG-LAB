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
    x1=ui->plainTextEdit->toPlainText().toFloat();
    y1=ui->plainTextEdit_2->toPlainText().toFloat();
    x2=ui->plainTextEdit_3->toPlainText().toFloat();
    y2=ui->plainTextEdit_4->toPlainText().toFloat();
    abs_x= x2>x1?(x2-x1):(x1-x2);
    abs_y= y2>y1?(y2-y1):(y1-y2);
    len = abs_x>abs_y?abs_x:abs_y;
    del_x=(x2-x1)/len;
    del_y=(y2-y1)/len;

}
 QImage image(400,400, QImage::Format_RGB888);
 //DDA
void MainWindow::on_pushButton_clicked()
{
    initial();

    float x=x1+(0.5*(x2>x1?1:(x2<x1)?(-1):0));
    float y=y1+(0.5*(y2>y1?1:(y2<y1)?(-1):0));
    int i=1;
    QRgb value;
    value=qRgb(255,255,255);   //set color of pixel as white
    while(i<len)
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

    float x=x1+(0.5*(x2>x1?1:(x2<x1)?(-1):0));
    float y=y1+(0.5*(y2>y1?1:(y2<y1)?(-1):0));
    int i=1;
    QRgb value;
    value=qRgb(255,255,255);   //set color of pixel as blue
    while(i<len)
    {
        if((i%2)==0)
        {
            image.setPixel(int(x),int(y),value);

             //draws pixel with value

        }
        x = x+del_x;
        y = y+del_y;
         i++;
    }
    ui->label_5->setPixmap(QPixmap::fromImage(image));

}


void MainWindow::on_pushButton_5_clicked()
{
    initial();

    float x=x1+(0.5*(x2>x1?1:(x2<x1)?(-1):0));
    float y=y1+(0.5*(y2>y1?1:(y2<y1)?(-1):0));
    int i=1;
    QRgb value;
    value=qRgb(255,255,255);   //set color of pixel as white
    while(i<len)
    {
        image.setPixel(int(x),int(y),value);
        image.setPixel(int(x),int(y+1),value);
        image.setPixel(int(x),int(y-1),value);
        x = x+del_x;
        y = y+del_y;
         //draws pixel with value
        i++;
    }

     ui->label_5->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::on_pushButton_3_clicked()
{
    initial();
   // int cnt=0;
    float x=x1+(0.5*(x2>x1?1:(x2<x1)?(-1):0));
    float y=y1+(0.5*(y2>y1?1:(y2<y1)?(-1):0));
    int i=1;
    QRgb value;
    value=qRgb(255,255,255);   //set color of pixel as white
    while(i<len)
    {
        if((i%6)<3)

       {
            image.setPixel(int(x),int(y),value);
        }
        x = x+del_x;
        y = y+del_y;
         //draws pixel with value
        i++;

    }


     ui->label_5->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_4_clicked()
{
    initial();

    float x=x1+(0.5*(x2>x1?1:(x2<x1)?(-1):0));
    float y=y1+(0.5*(y2>y1?1:(y2<y1)?(-1):0));
    int i=1;
    QRgb value;
    value=qRgb(255,255,255);   //set color of pixel as white
    while(i<len)
    {
        if(((i%9)<4) ||((i%9)==6))

       {
            image.setPixel(int(x),int(y),value);
        }
        x = x+del_x;
        y = y+del_y;
         //draws pixel with value
        i++;

    }


     ui->label_5->setPixmap(QPixmap::fromImage(image));

}
