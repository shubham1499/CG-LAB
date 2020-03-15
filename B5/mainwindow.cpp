#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QPainter"

QImage image(512 , 512 , QImage::Format_RGB555);

signed int midpoint = 512;

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
int MainWindow::sign(int val)
{
    if(val > 0)
        return 1;
    else if(val < 0)
        return -1;
    else
        return 0;
}
/*
void MainWindow::DDALineDrawingAlgo(int x1, int y1, int x2, int y2, QImage &img)
{
   float dx = abs( x2 - x1 );

   float dy = abs( y2 - y1 );

   float length;

   if(dx > dy )
       length = dx;
   else
       length = dy;

  float xinc = dx/length;
  float yinc = dy/length;

   float x = x1 + 0.5*sign(x2-x1);
   float y = y1 + 0.5*sign(y2-y1);

   int i =  0;

   while(i <= length)
   {
       img.setPixel(x , y , qRgb(0 , 255 , 0));
       x += xinc;
       y += yinc;
       i++;
   }
}*/
void MainWindow::BresenhamLineDrawingAlgo(int x1 , int y1 , int x2 , int y2 )
{
    int x , y , i , Interchange , dx , dy , Decision_Parameter , s1 , s2 ;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    x = x1;
    y = y1;
    s1 = sign(x2 - x1);
    s2 = sign(y2 - y1);
    i = 1;

     if(dy > dx)
     {
         int temp = dx;
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
        image.setPixel(x , y , qRgb(0 , 255 , 0));
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

}
void MainWindow::Hilbert(int level)
{

   image.fill(Qt::black);

  for(int i = 0; i < level ; i++)
  {
      midpoint = midpoint/2;
  }
   x = midpoint/2;
   y = midpoint/2;
   HilbertA(level);
   ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::HilbertA(int level)
{
  if(level > 0)
  {

      HilbertB(level-1);
      line(0 , midpoint);
      HilbertA(level-1);
      line(midpoint , 0);
      HilbertA(level -1);
      line(0 , -midpoint);
      HilbertC(level-1);

  }
}
void MainWindow::HilbertB(int level)
{
    if(level > 0)
    {
        HilbertA(level-1);
        line( midpoint ,0);
        HilbertB(level-1);
        line(0 , midpoint);
        HilbertB(level -1);
        line( -midpoint , 0);
        HilbertD(level-1);

    }
}
void MainWindow::HilbertC(int level)
{
    if(level > 0)
    {
        HilbertD(level-1);
        line(- midpoint , 0);
        HilbertC(level-1);
        line(0 , -midpoint);
        HilbertC(level -1);
        line( midpoint , 0);
        HilbertA(level-1);

    }
}
void MainWindow::HilbertD(int level)
{
    if(level > 0)
    {
        HilbertC(level-1);
        line(0 , -midpoint);
        HilbertD(level-1);
        line(-midpoint , 0);
        HilbertD(level -1);
        line(0 , midpoint);
        HilbertB(level-1);

    }
}
void MainWindow::line(int x1 , int y1)
{
  BresenhamLineDrawingAlgo(x , y , x+x1 , y+y1);
  x += x1;
  y += y1;

}
void MainWindow::on_pushButton_clicked()
{
   midpoint = 512;
   int level = ui->textEdit->toPlainText().toUInt();
   Hilbert(level);
   ui->label->setPixmap(QPixmap::fromImage(image));
}
