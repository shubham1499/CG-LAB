#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<math.h>
#include<GL/glut.h>
#include <unistd.h>

void Initialize() 
{	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,640,0,480);
}
void setPixel(GLint x,GLint y)
{
  	glBegin(GL_POINTS);
  	glVertex2i(x,y);
  	glEnd();
}
void Circle(int xCenter,int yCenter, int r)
{
  	int x=0,y=r;
  	int p = 3/2 - r;    
  	while(x<=y)
	{
    		setPixel(xCenter+x,yCenter+y);
    		setPixel(xCenter+y,yCenter+x);  
    		setPixel(xCenter-x,yCenter+y);
    		setPixel(xCenter+y,yCenter-x);
    		setPixel(xCenter-x,yCenter-y);
    		setPixel(xCenter-y,yCenter-x);
    		setPixel(xCenter+x,yCenter-y);
    		setPixel(xCenter-y,yCenter+x);
		if (p<0)
  			p += (2*x)+3;
		else 
		{
 			p += (2*(x-y))+5;
 			y -= 1;
    		}
    		x++;
  	}
	glFlush();
}
void animation()
{
	int x,y,i,j,k;        
	x=glutGet(GLUT_WINDOW_WIDTH);
	y=glutGet(GLUT_WINDOW_HEIGHT);
	for(k=90;k<450;k=k+30)
	{
		for(j=90;j<450;j=j+6)
		{
			for(i=90;i<450;i=i+6)
			{
				glColor3ub(10,10,254);
				Circle((x/2),(y/2)+50,150);
				Circle((x/2),(y/2)+50,3);
				glBegin(GL_LINES);
 					glVertex2f((x/2),(y/2)+50);
					glVertex2f(((x/2)-(130*cos(i*3.14/180))),((y/2+50)+(130*sin(i*3.14/180))));
 				glEnd();
				glColor3ub(254,5,254);
				glBegin(GL_LINES);
 					glVertex2f((x/2),(y/2)+50);
					glVertex2f(((x/2)-(110*cos(j*3.14/180))),((y/2+50)+(110*sin(j*3.14/180))));
 				glEnd();
				glColor3ub(5,254,254);
				glBegin(GL_LINES);
 					glVertex2f((x/2),(y/2)+50);
					glVertex2f(((x/2)-(90*cos(k*3.14/180))),((y/2+50)+(90*sin(k*3.14/180))));
 				glEnd();
				glFlush();
				//sleep(0.1);
				usleep(1000*1000);
        			glutSwapBuffers();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glFlush();
        		}
		}
	}
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(640,480);
 	glutInitWindowPosition(0,0);
  	glutCreateWindow("my first attempt");
  	glClearColor(1.0f,1.0f,1.0,0.0f);
  	glColor3ub(10,10,254);
  	Initialize();
  	glClear(GL_COLOR_BUFFER_BIT);
  	glutDisplayFunc(animation);
  	glutMainLoop();
	return 0;
}

