#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmath"

QImage image(600, 600, QImage::Format_RGB888);
QRgb value;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    x[0] = 200;
    y[0] = 200;
    x[1] = 400;
    y[1] = 200;
    x[2] = 200;
    y[2] = 400;
    x[3] = 400;
    y[3] = 400;
    for(int i=0; i<2; i++){
        x[i+4] = 202 + (50*i);
        y[i+4] = 202 + (50*i);
        x[i+6] = 202 + (50*i);
        y[i+6] = 302 + (50*i);
        x[i+8] = 302 + (50*i);
        y[i+8] = 202 + (50*i);
        x[i+10] = 302 + (50*i);
        y[i+10] = 302 + (50*i);
    }
}

void MainWindow :: matmul(float a[12][3], float b[3][3]){
    float temp[12][3];
    for(int i=0; i<12; i++){
        for(int j=0; j<3; j++){
            temp[i][j] = 0;
            for(int k=0; k<3; k++){
                temp[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for(int i=0; i<12; i++){
        for(int j=0; j<3; j++){
            a[i][j] = temp[i][j];
        }
    }


}

void MainWindow :: draw(){
    image.fill(qRgb(0,0,0));

    value = qRgb(255, 255, 255);
    bresenham(x[0], y[0], x[1], y[1]);
    bresenham(x[0], y[0], x[2], y[2]);
    bresenham(x[2], y[2], x[3], y[3]);
    bresenham(x[1], y[1], x[3], y[3]);

    float temp_x1 = (x[0] + x[1])/2;
    float temp_y1 = (y[0] + y[1])/2;
    float temp_x2 = (x[2] + x[3])/2;
    float temp_y2 = (y[2] + y[3])/2;
    bresenham(temp_x1, temp_y1, temp_x2, temp_y2);

    float temp_x3 = (x[0] + temp_x1)/2;
    float temp_y3 = (y[0] + temp_y1)/2;
    float temp_x4 = (x[2] + temp_x2)/2;
    float temp_y4 = (y[2] + temp_y2)/2;
    bresenham(temp_x3, temp_y3, temp_x4, temp_y4);

    temp_x3 = (x[1] + temp_x1)/2;
    temp_y3 = (y[1] + temp_y1)/2;
    temp_x4 = (x[3] + temp_x2)/2;
    temp_y4 = (y[3] + temp_y2)/2;
    bresenham(temp_x3, temp_y3, temp_x4, temp_y4);

    temp_x1 = (x[0] + x[2])/2;
    temp_y1 = (y[0] + y[2])/2;
    temp_x2 = (x[1] + x[3])/2;
    temp_y2 = (y[1] + y[3])/2;
    bresenham(temp_x1, temp_y1, temp_x2, temp_y2);

    temp_x3 = (x[0] + temp_x1)/2;
    temp_y3 = (y[0] + temp_y1)/2;
    temp_x4 = (x[1] + temp_x2)/2;
    temp_y4 = (y[1] + temp_y2)/2;
    bresenham(temp_x3, temp_y3, temp_x4, temp_y4);

    temp_x3 = (x[2] + temp_x1)/2;
    temp_y3 = (y[2] + temp_y1)/2;
    temp_x4 = (x[3] + temp_x2)/2;
    temp_y4 = (y[3] + temp_y2)/2;
    bresenham(temp_x3, temp_y3, temp_x4, temp_y4);

    for(int i=4; i<12; i++){
        seedfill(x[i], y[i]);
    }

    ui->label->setPixmap(QPixmap :: fromImage(image));
}

void MainWindow :: seedfill(float x, float y){
    QRgb curr = image.pixel(x, y);
    if(curr != value){
        image.setPixel(x, y, value);
        if(x<599 && x>0){
            seedfill(x+1, y);
            seedfill(x-1, y);
        }
        if(y>0 && y<599){
            seedfill(x, y+1);
            seedfill(x, y-1);
        }
    }

}

void MainWindow :: bresenham(float x1, float y1, float x2, float y2){

    int dx,dy,s1,s2,temp,flag_interchange,e,x,y;
    x=x1;
    y=y1;
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    s1=sign(x2-x1);
    s2=sign(y2-y1);

    if(dy>dx){
        temp=dx;
        dx=dy;
        dy=temp;
        flag_interchange=1;
    }
    else
        flag_interchange=0;

    e=2*dy-dx;

    for(int i=0;i<=dx;i++){
        image.setPixel(x,y,value);
        while(e>=0){
            if(flag_interchange==1)
                x=x+s1;
            else
                y=y+s2;
            e=e-2*dx;
        }
        if(flag_interchange==1)
            y=y+s2;
        else
            x=x+s1;
        e=e+2*dy;
    }
}

int MainWindow :: sign(float a){
    if(a<0){
        return -1;
    }
    return 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Draw_button_clicked()
{
    draw();
}

void MainWindow::on_rotateButton_clicked()
{
    float ang = 45;
    ang /= 180;
    ang *= 3.14159;

    float mat[12][3];
    float rot[3][3], trans[3][3];
    for(int i=0; i<12; i++){
        mat[i][0] = x[i];
        mat[i][1] = y[i];
        mat[i][2] = 1;
        if(i<3){
            for(int j=0; j<3; j++){
                rot[i][j] = 0;
                trans[i][j] = 0;
                if(i==j){
                    rot[i][j] = 1;
                    trans[i][j] = 1;
                }
            }
        }
    }
    trans[2][0] = -300;
    trans[2][1] = -300;

    matmul(mat, trans);

    rot[0][0] = cos(ang);
    rot[1][1] = cos(ang);
    rot[1][0] = sin(ang);
    rot[0][1] = (-1*rot[1][0]);
    matmul(mat, rot);

    trans[2][0] = 300;
    trans[2][1] = 300;

    matmul(mat, trans);

    for(int i=0; i<12; i++){
        x[i] = mat[i][0];
        y[i] = mat[i][1];
    }
    draw();
}
