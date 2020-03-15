#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<cmath>

QImage image(300,300,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dda(0,150,300,150);
    dda(150,0,150,300);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dda(int x1,int y1,int x2,int y2)
{
    float x,y,dx,dy,len;
    dx=(x2-x1);
    dy=(y2-y1);
    if(abs(dx)>=abs(dy))
        len=abs(dx);
    else
        len=abs(dy);
    dx=dx/len;
    dy=dy/len;
    x=x1+0.5*sign(x2-x1);
    y=y1+0.5*sign(y2-y1);
    int i=0;
    while(i<=len)
    {
        image.setPixel(x,y,qRgb(255,0,0));
        x=x+dx;
        y=y+dy;
        i++;
    }

    ui->label->setPixmap(QPixmap::fromImage(image));
}

int MainWindow::sign(int test)
{
    if(test<0)
        return -1;
    else
        return 1;
}

void MainWindow::on_pushButton_clicked()
{
    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    dda(x1+150,y1+150,x2+150,y2+150);
}

void MainWindow::x_reflect(int x1, int y1, int x2, int y2)
{
    int v[2][3]={{x1,y1,1},{x2,y2,1}};
    float x[3][3]={{1,0,0},{0,-1,0},{0,0,1}};
    multiply(v,x);
}

void MainWindow::y_reflect(int x1, int y1, int x2, int y2)
{
    int v[2][3]={{x1,y1,1},{x2,y2,1}};
    float x[3][3]={{-1,0,0},{0,1,0},{0,0,1}};
    multiply(v,x);
}

void MainWindow::xy_reflect(float x1,float y1,float x2,float y2)
{
    int v[2][3]={{x1,y1,1},{x2,y2,1}};
    float x[3][3]={{-1,0,0},{0,-1,0},{0,0,1}};
    multiply(v,x);
}

void MainWindow::on_pushButton_2_clicked()
{
    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    x_reflect(x1,y1,x2,y2);
}

void MainWindow::multiply(int v[2][3],float m[3][3])
{
    float result[2][3]={{0.0,0.0,0.0},{0.0,0.0,0.0}};
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                result[i][j]+=v[i][k]*m[k][j];
            }
        }
    }
    float x1,x2,y1,y2;
    x1=result[0][0];
    y1=result[0][1];
    x2=result[1][0];
    y2=result[1][1];
    dda(x1+150,y1+150,x2+150,y2+150);
}

void MainWindow::on_pushButton_3_clicked()
{
    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    y_reflect(x1,y1,x2,y2);
}

void MainWindow::on_pushButton_4_clicked()
{
    float x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    xy_reflect(x1,y1,x2,y2);
}

void MainWindow::arbitrary_rotate(float x1,float y1,float x2,float y2,float x3,float y3,float angle)
{

    int v[2][3]={{x1,y1,1},{x2,y2,1}};
    float an=((angle*3.14159)/180);
    float a,b;
    a=x3;
    b=y3;
    float tr[3][3]={{1,0,0},{0,1,0},{-a,-b,1}};
    float tr1[3][3]={{1,0,0},{0,1,0},{a,b,1}};

    float result1[2][3]={{0.0,0.0,0.0},{0.0,0.0,0.0}};
    float result2[2][3]={{0.0,0.0,0.0},{0.0,0.0,0.0}};
    float result3[2][3]={{0.0,0.0,0.0},{0.0,0.0,0.0}};
    float ro[3][3]={{cos(an),sin(an),0},{-sin(an),cos(an),0},{0,0,1}};

    for(int i=0;i<2;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                result1[i][j]+=v[i][k]*tr[k][j];
            }
        }
    }

    for(int i=0;i<2;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                result2[i][j]+=result1[i][k]*ro[k][j];
            }
        }
    }

    for(int i=0;i<2;i++)
    {
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                result3[i][j]+=result2[i][k]*tr1[k][j];
            }
        }
    }

    float x1x,x2x,y1y,y2y;
    x1x=result3[0][0];
    y1y=result3[0][1];
    x2x=result3[1][0];
    y2y=result3[1][1];
    dda(x1x+150,y1y+150,x2x+150,y2y+150);
}

void MainWindow::on_pushButton_5_clicked()
{
    float x1,y1,x2,y2,x3,y3;
    float angle;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    x3=ui->textEdit_5->toPlainText().toInt();
    y3=ui->textEdit_6->toPlainText().toInt();
    angle=ui->textEdit_7->toPlainText().toInt();

    arbitrary_rotate(x1,y1,x2,y2,x3,y3,angle);
}
