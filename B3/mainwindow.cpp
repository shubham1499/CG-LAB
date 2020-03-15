#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
         marker=1;
         ui->setupUi(this);
         flag=1;
         displayLine(100,100,100,300);
         displayLine(100,300,300,300);
         displayLine(100,100,300,100);
         displayLine(300,100,300,300);
         x_min=100;
         y_min=100;
         x_max=300;
         y_max=300;
         INSIDE=0;
         UP=1;
         BELOW=2;
         RIGHT=4;
         LEFT=8;
    }

MainWindow::~MainWindow()
{
    delete ui;
}
QImage image(700,700,QImage::Format_RGB888);
void MainWindow::cohenSutherlandClip(float x1, float y1, float x2, float y2)
{
    int code1 = computeCode(x1,y1);
    int code2 = computeCode(x2,y2);

    bool accept=false;
   while(1)
   {
    if((code1==0) && (code2==0))
    {
        //LINE IS INSIDE THE RECTANGLE
        accept = true;
        break;
    }
    else if((code1 & code2))
    {   //BOTH ENDPOINTS ARE OUTSIDE AND IN SAME REGION
        break;
    }
    else
    {
        //ONE ENDPOINT IS OUTSIDE AND THE OTHER IS INSIDE
        int code_out;
        float x,y;
        if(code1!=0)
            code_out = code1;
        else
            code_out = code2;

        if(code_out & UP)
        {
            x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
            y = y_max;
        }
        else if(code_out & BELOW)
        {
            x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
            y = y_min;
        }
        else if (code_out & RIGHT)
        {
            y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
            x = x_max;
        }
        else if (code_out & LEFT)
        {
            y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
            x = x_min;
        }
       if(code_out == code1)
       {
           x1=x;
           y1=y;
           code1=computeCode(x1,y1);
       }
       else
       {
           x2=x;
           y2=y;
           code2=computeCode(x2,y2);
       }
     }

   }
   if(accept == true)
   {
       displayLine(x1,y1,x2,y2);
   }
}
int MainWindow::computeCode(float x,float y)
{
    int temp_code = INSIDE;

    if(x<x_min)
        temp_code=temp_code | LEFT;
    else if(x>x_max)
        temp_code=temp_code | RIGHT;


    if(y<y_min)
        temp_code=temp_code | BELOW;
    else if(y>y_max)
        temp_code=temp_code | UP;


    return temp_code;
}

void MainWindow::displayLine(float x1, float y1, float x2, float y2)
{
   abs_x = (x2>x1?(x2-x1):(x1-x2));
   abs_y = (y2>y1?(y2-y1):(y1-y2));
   len   = (abs_x>abs_y?(abs_x):(abs_y));
   del_x = (x2-x1)/len;
   del_y = (y2-y1)/len;
   float x=x1+(0.5*(x2>x1?1:(x2<x1)?(-1):0));
   float y=y1+(0.5*(y2>y1?1:(y2<y1)?(-1):0));
   int i=0;
   QRgb value;
   value=qRgb(255,0,0);
   while(i<=len)
   {
       image.setPixel(x,y,value);
       x=x + del_x;
       y=y + del_y;
       i++;
   }
   ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(marker==1)
    {
        if(event->button()==Qt::RightButton)
            {
             marker=0;
            }
        else
        {
            float p = event->pos().x();
            float q = event->pos().y();
            if(flag==1)
            {
                a[0]=p;
                b[0]=q;
                flag=2;
            }
            else
            {
                a[1]=p;
                b[1]=q;
                flag=1;

               cohenSutherlandClip(a[0],b[0],a[1],b[1]);
            }
        }

    }
}
