#include <GL/glut.h>

GLfloat xRotated, yRotated, zRotated;


void redisplayFunc(void)
{
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);   // GL_COLOR_BUFFER_BIT - Indicates the buffers currently enabled for color  writing.
    
// clear the identity matrix.
   glLoadIdentity();
    /*
      glLoadIdentity replaces the current matrix with the identity matrix.	It is
  semantically equivalent to calling glLoadMatrix with the identity matrix


			      |	1   0	0   0  |
			      |		       |
			      |	0   1	0   0  |
			      |	0   0	1   0  |
			      |		       |
			      |	0   0	0   1  |

  but in some cases it is more efficient.
    */
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0,0.0,-5.0);
   /*
       glTranslate moves the	coordinate system origin to the	point specified	by
  (x,y,z).  The translation vector is used to compute a	4x4 translation
  matrix:

			    | 1	   0	0    x	 |
			    |			 |
			    | 0	   1	0    y	 |
			    |			 |
			    | 0	   0	1    z	 |
			    |			 |
			    | 0	   0	0    1	 |

  The current matrix (see glMatrixMode)	is multiplied by this translation
  matrix, with the product replacing the current matrix.  That is, if M	is
  the current matrix and T is the translation matrix, then M is	replaced with
  M � T.

  If the matrix	mode is	either GL_MODELVIEW or GL_PROJECTION, all objects
  drawn	after glTranslate is called are	translated.  Use glPushMatrix and
  glPopMatrix to save and restore the untranslated coordinate system.


   */
    // Red color used to draw.
    glColor3f(1.0, 0.0, 0.0); 
    // changing in transformation matrix.
    
    // rotation about X axis
    glRotatef(xRotated,1.0,0.0,0.0);   // xRotated is angle by which we want to rotate the cube in x direction
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
   glRotatef(zRotated,0.0,0.0,1.0);   // zRotated is the angle by which we want to rotated cube in z direction

   /*
     glRotate computes a matrix that performs a counterclockwise rotation of
  angle	degrees	about the vector from the origin through the point (x, y, z).

  The current matrix (see glMatrixMode)	is multiplied by this rotation
  matrix, with the product replacing the current matrix.  That is, if M	is
  the current matrix and R is the translation matrix, then M is	replaced with
  M � R.

  If the matrix	mode is	either GL_MODELVIEW or GL_PROJECTION, all objects
  drawn	after glRotate is called are rotated.  Use glPushMatrix	and
  glPopMatrix to save and restore the unrotated	coordinate system.
   */
    // scaling transfomation 
    glScalef(1.0,1.0,1.0);
   /*
     glScale produces a general scaling along the x, y, and z axes.  The three
  arguments indicate the desired scale factors along each of the three axes.
  The resulting	matrix is

			      |	 x   0	 0   0	|
			      |			|
			      |	 0   y	 0   0	|
			      |			|
			      |	 0   0	 z   0	|
			      |			|
			      |	 0   0	 0   1	|

  The current matrix (see glMatrixMode)	is multiplied by this scale matrix,
  with the product replacing the current matrix.  That is, if M	is the
  current matrix and S is the scale matrix, then M is replaced with M �	S.

  If the matrix	mode is	either GL_MODELVIEW or GL_PROJECTION, all objects
  drawn	after glScale is called	are scaled.  Use glPushMatrix and glPopMatrix
  to save and restore the unscaled coordinate system.
   */
// built-in (glut library) function , draw you a cube.
    glutWireCube(1.0);

    // Flush buffers to screen
    glFlush();  
   /* 
  Different GL implementations buffer commands in several different
  locations, including network buffers and the graphics	accelerator itself.
  glFlush empties all of these buffers,	causing	all issued commands to be
  executed as quickly as they are accepted by the actual rendering engine.
  Though this execution	may not	be completed in	any particular time period,
  it does complete in finite time.

  Because any GL program might be executed over	a network, or on an
  accelerator that buffers commands, all programs should call glFlush
  whenever they	count on having	all of their previously	issued commands
  completed.  For example, call	glFlush	before waiting for user	input that
  depends on the generated image.
   */   

    // sawp buffers called because we are using double buffering 
    glutSwapBuffers();
}

void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
   
 //Set a new projection matrix
    glMatrixMode(GL_PROJECTION); 
    /*
      
Parameters

  mode	Specifies which	matrix stack is	the target for subsequent matrix
	operations.  Three values are accepted:	GL_MODELVIEW, GL_PROJECTION,
	and GL_TEXTURE.	 The default value is GL_MODELVIEW.

Description

  glMatrixMode sets the	current	matrix mode.  mode can assume one of three
  values:

  GL_MODELVIEW	      Applies subsequent matrix	operations to the modelview
		      matrix stack.

  GL_PROJECTION	      Applies subsequent matrix	operations to the projection
		      matrix stack.

 
    */ 
    glLoadIdentity();   // replace the current matrix to identity matrix
   

   //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,1.0,20.0);

    glMatrixMode(GL_MODELVIEW);

    glViewport(0,0,x,y);  //Use the whole window for rendering
    /*
      Parameters

  x, y Specify the lower left corner of	the viewport rectangle,	in pixels.
       The default is (0,0).

  width, height
       Specify the width and height, respectively, of the viewport.  When a
       GL context is first attached to a window, width and height are set to
       the dimensions of that window.

Description

  glViewport specifies the affine transformation of x and y from normalized
  device coordinates to	window coordinates.  Let (x  , y  ) be normalized
                                                   nd   nd
  device coordinates.  Then the	window coordinates x , y ) are computed as
  follows:					    w	w

                                        width
			    x  = (x  +1)----- + x
			     w	   nd	  2  

                                        height
			    y  = (y  +1)------ + y
			     w	   nd	   2  

  Viewport width and height are	silently clamped to a range that depends on
  the implementation.  This range is queried by	calling	glGet with argument
  GL_MAX_VIEWPORT_DIMS.
    */
}

void idleFunc(void)
{
    // rotation around x axis 
    xRotated += 1.0;
    yRotated += 0.01;
    zRotated += 0.01;
    redisplayFunc();
}


int main (int argc, char **argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);

    //double buffering used to avoid flickering problem in animation
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB );  
    // window size
    glutInitWindowSize(400,400);
    // create the window 
    glutCreateWindow("My animation");

//    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
   /*
     Parameters

face

    Specifies the polygons that mode applies to. Must be GL_FRONT_AND_BACK for front- and back-facing polygons.
mode

    Specifies how polygons will be rasterized. Accepted values are GL_POINT, GL_LINE, and GL_FILL. The initial value is GL_FILL for both front- and back-facing polygons.

Description

glPolygonMode controls the interpretation of polygons for rasterization. face describes which polygons mode applies to: both front and back-facing polygons (GL_FRONT_AND_BACK). The polygon mode affects only the final rasterization of polygons. In particular, a polygon's vertices are lit and the polygon is clipped and possibly culled before these modes are applied.

Three modes are defined and can be specified in mode:

GL_POINT

    Polygon vertices that are marked as the start of a boundary edge are drawn as points. Point attributes such as GL_POINT_SIZE and GL_POINT_SMOOTH control the rasterization of the points. Polygon rasterization attributes other than GL_POLYGON_MODE have no effect.
GL_LINE

    Boundary edges of the polygon are drawn as line segments. Line attributes such as GL_LINE_WIDTH and GL_LINE_SMOOTH control the rasterization of the lines. Polygon rasterization attributes other than GL_POLYGON_MODE have no effect.
GL_FILL

    The interior of the polygon is filled. Polygon attributes such as GL_POLYGON_SMOOTH control the rasterization of the polygon. 
    */
    xRotated = yRotated = zRotated = 0.0;

    glClearColor(0.0,0.0,0.0,0.0);
    //Assign  the function used in events

    glutDisplayFunc(redisplayFunc);

    glutReshapeFunc(reshapeFunc);

    glutIdleFunc(idleFunc);
    //Let start glut loop
    glutMainLoop();
    
  return 0;
}

