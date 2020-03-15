#include<GL/glut.h>

GLfloat xRotated , yRotated , zRotated;

void displayFun()
{
   glClear(GL_COLOR_BUFFER_BIT);

   glLoadIdentity();

   glTranslatef(0.0 , 0.0 , -10.5);

  

   glColor3f(1.0 , 1.0 , 1.0);

   glScalef(2.0 , 2.0 , 2.0);

   glRotatef(xRotated , 1.0 , 0.0 , 0.0);  // rotation about x-axis
   
   glRotatef(yRotated , 0.0 , 1.0 , 0.0);

   glRotatef(zRotated , 0.0 , 0.0 , 1.0);
  //  glutWireCube(2.0);

   glBegin(GL_QUADS);
   glColor3f(1.0 , 0.0 , 1.0);
   glVertex3f(0.0 , 0.0 , 0.0);
   glVertex3f(1.0 , 0.0 , 0.0);
   glVertex3f(1.0 , 1.0 , 0.0);
   glVertex3f(0.0 , 1.0 , 0.0);
  
   glColor3f(1.0 , 0.0 , 0.0);
   glVertex3f(0.0 , 0.0 , 0.0);
   glVertex3f(0.0 , 0.0 , 1.0);
   glVertex3f(1.0 , 0.0 , 1.0);
   glVertex3f(1.0 , 0.0 , 0.0);

   glColor3f(1.0 , 1.0 , 0.0);
   glVertex3f(0.0 , 0.0 , 0.0);
   glVertex3f(0.0 , 1.0 , 0.0);
   glVertex3f(0.0 , 1.0 , 1.0);
   glVertex3f(0.0 , 0.0 , 1.0);

   glColor3f(0.0 , 1.0 , 0.0);
   glVertex3f(1.0 , 1.0 , 1.0);
   glVertex3f(1.0 , 1.0 , 0.0);
   glVertex3f(1.0 , 0.0 , 0.0);
   glVertex3f(1.0 , 0.0 , 1.0);
 
   glColor3f(0.0 , 1.0 , 1.0);
   glVertex3f(1.0 , 1.0 , 1.0);
   glVertex3f(0.0 , 1.0 , 1.0);
   glVertex3f(0.0 , 1.0 , 0.0);
   glVertex3f(1.0 , 1.0 , 0.0);

   glColor3f(0.0 , 0.0 , 1.0);
   glVertex3f(1.0 , 1.0 , 1.0);
    glVertex3f(0.0 , 1.0 , 1.0);
   glVertex3f(0.0 , 0.0 , 1.0);
   glVertex3f(1.0 , 0.0 , 1.0);
   
   glEnd();
   glFlush();

   glutSwapBuffers();

}
void ReshapeFun(int x , int y)
{
   if(x == 0 || y==0)
    return; 

   glMatrixMode(GL_PROJECTION);

   glLoadIdentity();

   gluPerspective(30.0 , (GLdouble)x/(GLdouble)y , 0.5 , 20.0);

   glMatrixMode(GL_MODELVIEW);

   glViewport(0 , 0 , x , y);
}

void idelFunc()
{
  xRotated += 1.0;
  yRotated += 1.0;
  zRotated += 1.0;
  displayFun();
}
int main(int argc , char **argv)
{
   glutInit(&argc , argv);

   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

   glutInitWindowSize(400 , 400);

   glutCreateWindow("It's me");

   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    xRotated = 0.0;

    glClearColor(0.0,0.0,0.0,0.0);
    //Assign  the function used in events

    glutDisplayFunc(displayFun);

    glutReshapeFunc(ReshapeFun);

    glutIdleFunc(idelFunc);
    //Let start glut loop
    glutMainLoop();
}
