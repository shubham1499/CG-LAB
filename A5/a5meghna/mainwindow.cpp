#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
#include<QtGui>
#include<QApplication>
#include<QColorDialog>
 QImage image(300,300,QImage::Format_RGB888);
 QImage image1(300,300,QImage::Format_RGB888);

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
void MainWindow::bresenham(float x1,float y1,float x2,float y2)
{
    float x , y , i ,dx,dy,s1,s2;
    int Interchange, Decision_Parameter ;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    x = x1;
    y = y1;
    s1 = sign(x2,x1);
    s2 = sign(y2,y1);
    i = 1;

     if(dy > dx)
     {
         float temp = dx;
             dx = dy;
             dy = temp;
           Interchange = 1;
     }
    else
     {
         Interchange = 0;
     }
   Decision_Parameter = 2*dy - dx;

    while( i <= dx)
      {
        image.setPixel(x , y , qRgb(255, 255 , 255));
        while(Decision_Parameter >= 0)
        {
            if(Interchange == 1)
            {
                x += s1;
            }
            else
            {
                y += s2;
            }
              Decision_Parameter -= 2*dx;

        }
        if(Interchange == 1)
        {
            y += s2;
        }
        else
        {
            x += s1;
        }
         Decision_Parameter += 2*dy;
        i++;
      }
 //ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::bresenham1(float x1,float y1,float x2,float y2)
{
    float x , y , i ,dx,dy,s1,s2;
    int Interchange, Decision_Parameter ;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    x = x1;
    y = y1;
    s1 = sign(x2,x1);
    s2 = sign(y2,y1);
    i = 1;

     if(dy > dx)
     {
         float temp = dx;
             dx = dy;
             dy = temp;
           Interchange = 1;
     }
    else
     {
         Interchange = 0;
     }
   Decision_Parameter = 2*dy - dx;

    while( i <= dx)
      {
        image1.setPixel(x , y , qRgb(255, 255 , 255));
        while(Decision_Parameter >= 0)
        {
            if(Interchange == 1)
            {
                x += s1;
            }
            else
            {
                y += s2;
            }
              Decision_Parameter -= 2*dx;

        }
        if(Interchange == 1)
        {
            y += s2;
        }
        else
        {
            x += s1;
        }
         Decision_Parameter += 2*dy;
        i++;
      }
 //ui->label->setPixmap(QPixmap::fromImage(image));
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
void MainWindow::draw()
{


    width=ui->label->width();
    height=ui->label->height();


    c1=width/2;
    c2=height/2;

    float x1,y1,side;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    side=ui->textEdit_3->toPlainText().toFloat();

    bresenham(c1,0,c1,height);
    bresenham(0,c2,width,c2);

    calculate(side);
    bresenham(x1+c1,c2-y1,x1+c1+side,c2-y1);
    bresenham(x1+c1,c2-y1-side,x1+c1+side,c2-y1-side);
    bresenham(x1+c1,c2-y1,x1+c1,c2-y1-side);
    bresenham(x1+c1+side,c2-y1,x1+c1+side,c2-y1-side);

    bresenham(x1+c1,c2-y1-g1,x1+c1+side,c2-y1-g1);
     bresenham(x1+c1,c2-y1-2*g1,x1+c1+side,c2-y1-2*g1);
      bresenham(x1+c1,c2-y1-3*g1,x1+c1+side,c2-y1-3*g1);

      bresenham(c1+x1+g1,c2-y1-side,c1+x1+g1,c2-y1);
      bresenham(c1+x1+2*g1,c2-y1-side,c1+x1+2*g1,c2-y1);
      bresenham(c1+x1+3*g1,c2-y1-side,c1+x1+3*g1,c2-y1);

      seedfill(c1+x1+side/8,c2-y1-side/8);
      seedfill(c1+x1+5*side/8,c2-y1-side/8);
      seedfill(c1+x1+3*side/8,c1-y1-3*side/8);
      seedfill(c1+x1+7*side/8,c2-y1-3*side/8);
      seedfill(c1+x1+side/8,c2-y1-5*side/8);
      seedfill(c1+x1+5*side/8,c2-y1-5*side/8);
      seedfill(c1+x1+3*side/8,c2-y1-7*side/8);
      seedfill(c1+x1+7*side/8,c2-y1-7*side/8);

      ui->label->setPixmap(QPixmap::fromImage(image));

      arr[0][0]=x1;
      arr[0][1]=y1;
      arr[1][0]=x1+side;
      arr[1][1]=y1;
      arr[2][0]=x1;
      arr[2][1]=y1-side;
      arr[3][0]=x1+side;
      arr[3][1]=y1-side;

      float theta;
      theta=(45*3.14)/180;
     float a,b,c,d;
      a=cos(theta);
      b=sin(theta);
      c=-sin(theta);
      d=cos(theta);

       rot[0][0]=a;
       rot[0][1]=b;
       rot[1][0]=c;
       rot[1][1]=d;
 }

void MainWindow::on_pushButton_clicked()
{
    draw();
}
void MainWindow::seedfill(float x,float y)
{   QRgb color;
    color=qRgb(255,255,255);

    QRgb current=image.pixel(int(x),int(y));
    if((current!=color))
    {
        image.setPixel(int (x),int (y),color);
        seedfill(x+1,y);
         seedfill(x-1,y);
          seedfill(x,y+1);
           seedfill(x,y-1);
    }

}

void MainWindow::seedfill1(float x,float y)
{   QRgb color;
    color=qRgb(255,255,255);

    QRgb current=image1.pixel(int(x),int(y));
    if((current!=color))
    {
        image1.setPixel(int (x),int (y),color);
        seedfill1(x+1,y);
         seedfill1(x-1,y);
          seedfill1(x,y+1);
           seedfill1(x,y-1);
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    float x1,y1,side;
    x1=ui->textEdit->toPlainText().toFloat();
    y1=ui->textEdit_2->toPlainText().toFloat();
    side=ui->textEdit_3->toPlainText().toFloat();

    multiply(arr,rot);

    bresenham1(c1+a1,c2-b1,c1+a2,c2-b2);
    bresenham1(c1+a1,c2-b1,c1+a3,c2-b3);
    bresenham1(c1+a2,c2-b2,c1+a4+1,c2-b4+1);
    bresenham1(c1+a3,c2-b3,c1+a4,c2-b4);

       calculate(side);
       float m1,m2,m3,m4;
       m1=(a1+a2)/2;
        m2=(b1+b2)/2;
         m3=(a3+a4)/2;
          m4=(b3+b4)/2;
         //horizontal lines
       bresenham1(c1+m1,c2-m2+1,c1+m3,c2-m4+1);
       bresenham1(c1+(a1+m1)/2,c2-(b1+m2)/2+1,c1+(a3+m3)/2,c2-(b3+m4)/2+1);
       bresenham1(c1+(a2+m1)/2,c2-(b2+m2)/2+1,c1+(a4+m3)/2,c2-(b4+m4)/2+1);

       float m5,m6,m7,m8;
       m5=(a1+a3)/2;
        m6=(b1+b3)/2;
         m7=(a2+a4)/2;
          m8=(b2+b4)/2;
        //vertical lines

          bresenham1(c1+m5,c2-m6,c1+m7,c2-m8);
          bresenham1(c1+(a1+m5)/2,c2-(b1+m6)/2,c1+(a2+m7)/2,c2-(b2+m8)/2);
          bresenham1(c1+(a3+m5)/2,c2-(b3+m6)/2,c1+(a4+m7)/2,c2-(b4+m8)/2);



//          seedfill1(c1+a1+side/8,c2-b1-side/8);
          seedfill1(c1+a1+5*side/8,c2-b1-side/8);
         // seedfill1(c1+a1+3*side/8,c1-b1-3*side/8);
         // seedfill1(c1+a1+7*side/8,c2-b1-3*side/8);
         //seedfill1(c1+a1+side/8,c2-b1-5*side/8);
         // seedfill1(c1+a1+5*side/8,c2-b1-5*side/8);
        // seedfill1(c1+a1+3*side/8,c2-b1-7*side/8);
        //  seedfill1(c1+a1+7*side/8,c2-b1-7*side/8);

         ui->label_5->setPixmap(QPixmap::fromImage(image1));
 }
 void MainWindow::calculate(float side)
 {
     g1=side/4;
 }
 void MainWindow::multiply(float arr[10][10],float rot[10][10])
 {
     int i,j,k;
    for(i=0;i<4;i++)
       {
        for(j=0;j<2;j++)
        {
            result[i][j]=0;

             for(k=0;k<2;k++)
             {
               result[i][j]+=arr[i][k]*rot[k][j];
             }

        }

       }

    a1=result[0][0];
    b1=result[0][1];
    a2=result[1][0];
    b2=result[1][1];
    a3=result[2][0];
    b3=result[2][1];
    a4=result[3][0];
    b4=result[3][1];

}
