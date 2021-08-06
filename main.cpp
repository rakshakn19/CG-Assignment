#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define PI 3.1416
#define WELSCREEN 1
int screen=1;
//int x1,y1,x2,y2;
int x=200,y=200;
//first program global variables
int x1=200,y11=200,x2=600,y2=600;

//2nd program global variables

int x22=100,y22=100;
int where_to_rotate = 0;
float rotate_angle=0;
float translate_x=0,translate_y=0;

//3rd program global variables

GLfloat vertices[] = {-1,-1,-1,
1,-1,-1,
1,1,-1,
-1,1,-1,
-1,-1,1,
1,-1,1,
1,1,1,
-1,1,1
};
GLfloat colors[]={0,0,0,
1,0,0,
1,1,0,
0,1,0,
0,0,1,
1,0,1,
1,1,1,
0,1,1};
GLubyte cubeIndices[]={0,3,2,1,
2,3,7,6,
0,4,7,3,
1,2,6,5,
4,5,6,7,
0,1,5,4};
static GLfloat theta[]={0,0,0};
static GLint axis=2;

//clipping window global variables
double xmin=50,ymin=50,xmax=100,ymax=100;
double xvmin=200,yvmin=200,xvmax=300,yvmax=300;
const int LEFT=1;
const int RIGHT=2;
const int BOTTOM=4;
const int TOP=8;
//sirpenskie gasket global variables

typedef float point[3];
point v[]= {{0, 0, 1}, {0, 1, 0}, {-1, -0.5, 0}, {1, -0.5, 0}};
int n=2;
//9th program global variables

int x10,y10,x20,y20,x30,y30,x40,y40;

//Bresenhams Line drawing Algorithm

void draw_pixel(int x,int y)
{
    glColor3f(1,.8,0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();

}
void bresenhams_line_draw(int x1,int y1,int x2,int y2)
{

    int dx=x2-x1;
    int dy=y2-y1;
    int m=dy/dx;

    if(m<1)
    {
        int decision_parameter=2*dy-dx;
        int x=x1;
        int y=y1;
        if(dx<0)
        {
            x=x2;
            y=y2;
            x2=x1;

        }
        draw_pixel(x,y);
        while(x<x2){
            if(decision_parameter>=0){
                x=x+1;
                y=y+1;
                decision_parameter=decision_parameter+2*dy-2*dx*(y+1-y);

            }
            else{
                x=x+1;
                y=y;
                decision_parameter=decision_parameter+2*dy-2*dx*(y-y);
            }
            draw_pixel(x,y);
            glFlush();
        }
    }
    else if(m>1)
    {
        int decision_parameter=2*dx-dy;
        int x=x1;
        int y=y1;
        if(dy<0){
            x=x2;
            y=y2;
            y2=y1;
        }
        draw_pixel(x,y);
        while(y<y2){
            if(decision_parameter>=0){
                x=x+1;
                y=y+1;
                decision_parameter=decision_parameter+2*dx-2*dy*(x+1-x);

            }
            else{
                y=y+1;
                x=x;
                decision_parameter=decision_parameter+2*dx-2*dy*(x-x);
            }
            draw_pixel(x,y);
            glFlush();        }
    }
    else if(m==1){
        int x=x1;
        int y=y1;
        draw_pixel(x,y);
        while(x<x2){
            x=x+1;
            y=y+1;
            draw_pixel(x,y);
            glFlush();
        }
    }


}
//program 2 triangle

void draw_pixel2(float x1,float y1)
{
    glPointSize(5);
    glColor3f(1,0,1);
    glBegin(GL_POINTS);
    glVertex2f(x1,y1);
    glEnd();
}

void triangle1(int x,int y)
{
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(x,y);
    glVertex2f(x+400,y+300);
    glVertex2f(x+300,y+0);
    glEnd();
}
void rotateMenu (int option){
    if(option == 1){
        where_to_rotate = 1;
    }
    if(option==2){
        where_to_rotate = 2;
    }
    if(option==3){
        where_to_rotate = 3;
    }
}


//Cohen Sutherland Line Clipping algorithm
int ComputOutCode(double x,double y)
{

    int code=0;
    if(y>ymax)
        code |=TOP;
    else if(y<ymin)
        code |=BOTTOM;
    else if(x>xmax)
        code |=RIGHT;
    else if(x<xmin)
        code |=LEFT;
    return code;
}


void CohenSutherland(double x0,double y0,double x1,double y1)
{

  int outcode0,outcode1,outcodeOut;
  bool accept=false,done=false;

  outcode0=ComputOutCode(x0,y0);
  outcode1=ComputOutCode(x1,y1);


  do
  {

      if(!(outcode0 |outcode1))
      {
          accept=true;
          done=true;

      }
      else if(outcode0&outcode1)
        done=true;
      else
      {

          double x,y;
          double m=(y1-y0)/(x1-x0);
          outcodeOut=outcode0?outcode0:outcode1;

          if(outcodeOut& TOP)
          {
              x=x0+(1/m)*(ymax-y0);
              y=ymax;


          }
          else if(outcodeOut&BOTTOM)
          {
              x=x0+(1/m)*(ymin-y0);
              y=ymin;

          }

          else if(outcodeOut&RIGHT)
          {
              x=xmax;
              y=y0+(1/m)*(xmax-x0);
          }
          else
          {
              x=xmin;
              y=y0+(1/m)*(xmin-x0);

          }
          if(outcodeOut ==outcode0)
          {
              x0=x;
              y0=y;
              outcode0 =ComputOutCode(x0,y0);
          }
          else
            {
                x1 = x;
                y1 = y;
                outcode1 = ComputOutCode(x1,y1);
            }


      }

  }
  while(!done);
  glColor3f(1,0,0);
   glBegin(GL_LINES);
    glVertex2d(x0,y0);
    glVertex2d(x1,y1);
    glEnd();

   glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    glEnd();


  if(true)
  {

      double sx=(xvmax-xvmin)/(xmax-xmin);
      double sy=(yvmax-yvmin)/(ymax-ymin);

      double vx0=xvmin+(x0-xmin)*sx;
      double vy0=yvmin+(y0-ymin)*sy;

      double vx1=xvmin+(x1-xmin)*sx;
      double vy1=yvmin+(y1-ymin)*sy;

      glBegin(GL_LINE_LOOP);
      glVertex2f(xvmin,yvmin);
      glVertex2f(xvmax,yvmin);
      glVertex2f(xvmax,yvmax);
      glVertex2f(xvmin,yvmax);
      glEnd();

      glBegin(GL_LINES);
      glVertex2d(vx0,vy0);
      glVertex2d(vx1,vy1);
      glEnd();


  }


}

//3D sierpinski gasket
void triangle(point a, point b, point c)
{
    glBegin(GL_POLYGON);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}
void divide_triangle(point a, point b, point c, int n)
{
    point v1,v2,v3;
    int j;
    if(n>0)
    {
        for(j=0; j<3; j++)
            v1[j] = (a[j]+b[j])/2;
        for(j=0; j<3; j++)
            v2[j] = (a[j]+c[j])/2;
        for(j=0; j<3; j++)
            v3[j] = (c[j]+b[j])/2;
        divide_triangle(a,v1,v2,n-1);
        divide_triangle(c,v2,v3,n-1);
        divide_triangle(b,v3,v1,n-1);
    }
    else
        triangle (a,b,c);
}

void tetrahedron(int n)
{
    glColor3f(1, 0, 0);
    divide_triangle(v[0], v[1], v[2], n);
    glColor3f(0, 1, 0);
    divide_triangle(v[3], v[2], v[1], n);
    glColor3f(0, 0, 1);
    divide_triangle(v[0], v[3], v[1], n);
    glColor3f(0, 0, 0);
    divide_triangle(v[0], v[2], v[3], n);
}

void myReshape(int w,int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
        glOrtho(-2, 2, -2*(GLfloat)h/(GLfloat)w, 2*(GLfloat)h/(GLfloat)w, -10, 10);
    else
        glOrtho(-2*(GLfloat)w/(GLfloat)h, 2*(GLfloat)w/(GLfloat)h, -2, 2, -10, 10);
    glMatrixMode(GL_MODELVIEW);



}
//Tea pot an a table (Light properties
void teapot(GLfloat x,GLfloat y,GLfloat z)
{
    glPushMatrix();
    glTranslatef(x,y,z);

    glutSolidTeapot(0.1);
    glPopMatrix();
}
void tableTop(GLfloat x,GLfloat y,GLfloat z)
{
    glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(.6,.02,.5);
    glutSolidCube(1);
    glPopMatrix();
}
void tableLeg(GLfloat x,GLfloat y,GLfloat z)
{
    glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(.02,.3,.02);
    glutSolidCube(1);
    glPopMatrix();
}
void wall(GLfloat x,GLfloat y,GLfloat z)
{
    glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(1,1,0.02);
    glutSolidCube(1);
    glPopMatrix();
}
void light()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    GLfloat mat_ambient[]={1,1,1,1};
    GLfloat mat_diffuse[]={.5,.5,.5,1};
    GLfloat mat_specular[]={1,1,1,1};
    GLfloat mat_shininess[]={50.0f};
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

    GLfloat light_position[]={2,6,3,1};
    GLfloat light_intensity[]={.7,.7,.7,1};

    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_intensity);
}


//scan line fill algorithm
void edgedetect(float x1,float y1,float x2,float y2,int *left_edge,int *right_edge)
{
    float x_slope,x,temp;
    int i;
    if((y2-y1)<0)
    {
        temp=y1;
        y1=y2;
        y2=temp;

        temp=x1;
        x1=x2;
        x2=temp;

    }
    if((y2-y1)!=0)
        x_slope=(x2-x1)/(y2-y1);
    else
        x_slope=x2-x1;
    x=x1;
    for(i=y1;i<=y2;i++)
    {
        if(x< left_edge[i])
            left_edge[i]=x;
        if(x>right_edge[i])
            right_edge[i]=x;
        x=x+x_slope;
    }
}
void draw_pixel1(int x,int y)
{
    glColor3f(1,0,1);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
 void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
    int left_edge[500],right_edge[500];
    int i,y;

    for(i=0;i<=500;i++)
    {
        left_edge[i]=500;
        right_edge[i]=0;
    }
    edgedetect(x1,y1,x2,y2,left_edge,right_edge);
    edgedetect(x2,y2,x3,y3,left_edge,right_edge);
    edgedetect(x3,y3,x4,y4,left_edge,right_edge);
    edgedetect(x4,y4,x1,y1,left_edge,right_edge);
    for(y=0;y<=500;y++)
    {
        if(left_edge[y]<=right_edge[y])
        {
            for(i=left_edge[y];i<=right_edge[y];i++)
            {
                draw_pixel1(i,y);
                glFlush();
            }
        }
    }
}
//3rd spin cube
void spinCube()
{

    theta[axis]+=3;
    if(theta[axis]>360)
        theta[axis]-=360;
    glutPostRedisplay();

}
void mouse(int btn,int state,int x,int y)
{

    if(btn==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
        axis=0;

    if(btn==GLUT_MIDDLE_BUTTON&&state==GLUT_DOWN)
        axis=1;
    if(btn==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
        axis=2;
}
//Bezier curve
float theta1 = 0;
struct point1
{
    GLfloat x, y, z;
};

int factorial (int n)
{
    if (n<=1)
        return (1);
    else
        n = n * factorial ( n-1 );
    return n;
}

void computeNcR (int n, int *hold_ncr_values)
{
    int r;
    for (r=0; r<=n; r++)
        {
            hold_ncr_values [r] = factorial (n) / ( factorial (n-r) * factorial (r) );
    }
}

void computeBezierPoints (float t, point1 *actual_bezier_point, int number_of_control_points, point1 *control_points_array, int *hold_ncr_values) // 5 parameters
{
    int i, n = number_of_control_points - 1;
    float bernstein_polynomial;
    actual_bezier_point -> x = 0;
    actual_bezier_point -> y = 0;
    actual_bezier_point -> z = 0;
    for ( i=0; i<number_of_control_points; i++ )
    {
        bernstein_polynomial = hold_ncr_values [i] * pow(t, i) * pow( 1-t, n-i);
        actual_bezier_point->x += bernstein_polynomial * control_points_array [i].x; actual_bezier_point->y += bernstein_polynomial * control_points_array [i].y;
        actual_bezier_point->z += bernstein_polynomial * control_points_array [i].z;
    }
}

void bezier (point1 *control_points_array, int number_of_control_points, int number_of_bezier_points)
{
    point1 actual_bezier_point;
    float t;
    int *hold_ncr_values, i;
    hold_ncr_values = new int [number_of_control_points];
    computeNcR (number_of_control_points - 1, hold_ncr_values);
    glBegin (GL_LINE_STRIP);
    for(i=0; i<=number_of_bezier_points; i++)
        {
            t=float (i) / float (number_of_bezier_points);
            computeBezierPoints ( t, &actual_bezier_point, number_of_control_points, control_points_array, hold_ncr_values );// 5 parameters
            glVertex2f (actual_bezier_point.x, actual_bezier_point.y);
    }
    glEnd ();
    delete [] hold_ncr_values;
}
void init8 ()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
}
void display8()
{
    glClear (GL_COLOR_BUFFER_BIT);
    int number_of_control_points= 4, number_of_bezier_points= 20;
    point1 control_points_array[4]= {{100, 400, 0}, {150, 450, 0}, {250, 350, 0},{300, 400, 0}};
    control_points_array[1].x += 50 * sin (theta1 * PI/180.0);
    control_points_array[1].y += 25 * sin (theta1 * PI/180.0);
    control_points_array[2].x -= 50 * sin ((theta1 +30) * PI/180.0);
    control_points_array[2].y -= 50 * sin ((theta1 +30) * PI/180.0);
    control_points_array[3].x -= 25 * sin ((theta1 -30) * PI/180.0);
    control_points_array[3].y += sin ((theta1 -30) * PI/180.0); theta1 += 2;
    glPushMatrix ();
    glPointSize (5);
    glColor3f (1, 0.4, 0.2);
    for (int i=0; i<50; i++)
    {
        glTranslatef(0, -0.8, 0 );
        bezier(control_points_array, number_of_control_points, number_of_bezier_points);
    }
    glColor3f(1, 1, 1);
    for(int i=0; i<50; i++)
    {
        glTranslatef(0, -0.8, 0);
        bezier(control_points_array, number_of_control_points, number_of_bezier_points);
    }
    glColor3f(0, 1, 0);
    for(int i=0; i<50; i++)
    {
        glTranslatef(0, -0.8, 0);
        bezier(control_points_array, number_of_control_points, number_of_bezier_points);
    }
    glPopMatrix();
    glLineWidth(5);
    glColor3f(0.7, 0.5,0.3);
    glBegin(GL_LINES);
    glVertex2f(100,400);
    glVertex2f(100,40);
    glEnd();
    glutPostRedisplay();
    glutSwapBuffers();
}
//List menu
void lists(int option)
{
    if (option==1){

            bresenhams_line_draw(x1,y11,x2,y2);
            glFlush();
    }
    if(option==2)
    {

        glClear(GL_COLOR_BUFFER_BIT);
        glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
        glClearColor(1,1,0,1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-800,800,-800,800);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(1,0,0);
        glBegin(GL_POLYGON);
        glVertex2f(100,100);
        glVertex2f(100+400,100+300);
        glVertex2f(100+300,100+0);
        glEnd();
        glFlush();
         glutCreateMenu(rotateMenu);
        glutAddMenuEntry("rotate around ORIGIN",1);
        glutAddMenuEntry("rotate around FIXED POINT",2);
        glutAddMenuEntry("Stop Rotation",3);
        glutAttachMenu(GLUT_RIGHT_BUTTON);

        glColor3f(0,1,0);
        draw_pixel(0,0);
        if(where_to_rotate == 1){
            translate_x = 0;
            translate_y = 0;
            rotate_angle += 1;
        }
        if(where_to_rotate == 2){
            translate_x = x;
            translate_y = y;
            rotate_angle += 1;
            glColor3f(0,0,1);
            draw_pixel2(x,y);
        }
        glTranslatef(translate_x,translate_y,0);
        glRotatef(rotate_angle,0,0,1);
        glTranslatef(-translate_x,-translate_y,0);


        glutPostRedisplay();
        glutSwapBuffers();


        glFlush();

       /* glClear(GL_COLOR_BUFFER_BIT);
        glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
        glClearColor(1,1,1,1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-800,800,-800,800);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(1,1,1);
        draw_pixel2(0,0);

        if(where_to_rotate == 1){
            translate_x = 0;
            translate_y = 0;
            rotate_angle += 1;
        }
        if(where_to_rotate == 2){
            translate_x = 100;
            translate_y = 100;
            rotate_angle += 1;
            glColor3f(0,0,1);
            draw_pixel2(100,100);
        }
        glTranslatef(translate_x,translate_y,0);
        glRotatef(rotate_angle,0,0,1);
        glTranslatef(-translate_x,-translate_y,0);

        triangle(translate_x,translate_y);
        glutPostRedisplay();
        glutSwapBuffers();

        glutCreateMenu(rotateMenu);
        glutAddMenuEntry("rotate around ORIGIN",1);
        glutAddMenuEntry("rotate around FIXED POINT",2);
        glutAddMenuEntry("Stop Rotation",3);
        glutAttachMenu(GLUT_RIGHT_BUTTON);

        glFlush();*/
    }

    if (option==3){
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glRotatef(theta[0],1,0,0);
        glRotatef(theta[1],0,1,0);
        glRotatef(theta[2],0,0,1);
        glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,cubeIndices);
        glutSwapBuffers();

        glutInitWindowSize(500,500);
        glEnable(GL_DEPTH_TEST);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3,GL_FLOAT,0,vertices);
        glColorPointer(3,GL_FLOAT,0,colors);
        glColor3f(1,1,1);


        glutMouseFunc(mouse);

        spinCube();

        glutSwapBuffers();
        glutMainLoop();

    }

    if (option==5){

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1,0,0);
        double x3=60,y3=20,x4=80,y4=120;
      // double x3=100,y3=50,x4=140,y4=160;
        glBegin(GL_LINES);
        glVertex2d(x3,y3);
        glVertex2d(x4,y4);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex2f(xmin,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymax);
        glVertex2f(xmin,ymax);
        glEnd();

        CohenSutherland(x3,y3,x4,y4);

        glFlush();

    }

    if(option==7)
    {

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        tetrahedron(n);
        glFlush();

    }
    if(option==6)
    {

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0,0,0,1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1,1,-1,1,-1,10);
        glMatrixMode(GL_MODELVIEW);
        GLfloat teapotP=-0.07,tabletopP=-.15,tablelegP=.2,wallP=0.5;
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(-2,2,5,0,0,0,0,1,0);
        light();
        teapot(0,teapotP,0);
        tableTop(0,tabletopP,0);

        tableLeg(tablelegP,-0.3,tablelegP);
        tableLeg(-tablelegP,-0.3,tablelegP);
        tableLeg(-tablelegP,-0.3,-tablelegP);
        tableLeg(tablelegP,-0.3,-tablelegP);

        wall(0,0,-wallP);
        glRotatef(90,1,0,0);

        wall(0,0,wallP);
        glRotatef(90,0,1,0);

        wall(0,0,wallP);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_NORMALIZE);
        glEnable(GL_DEPTH_TEST);

        glFlush();
    }
    if(option==8)
    {

        display8();
        glutMainLoop();
    }
    if(option==9)
    {

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glDisable(GL_LIGHT0|GL_NORMALIZE|GL_LIGHTING|GL_DEPTH_TEST);
        glClearColor(1,1,1,0);
        x10=200,y10=200;
        x20=100,y20=300;
        x30=200,y30=400;
        x40=300,y40=300;


        glColor3f(0,0,1);
        glBegin(GL_LINE_LOOP);
            glVertex2f(x10,y10);
            glVertex2f(x20,y20);
            glVertex2f(x30,y30);
            glVertex2f(x40,y40);
        glEnd();
        scanfill(x10,y10,x20,y20,x30,y30,x40,y40);
        glFlush();

    }
}

void init()
{

    glClearColor(.5,.5,1,1);
    gluOrtho2D(0,500,0,500);
}
void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

}
int main(int argc,char **argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Menu Driven Program");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
    //glEnable(GL_DEPTH_TEST);

    glutCreateMenu(lists);
    glutAddMenuEntry("1.Implement Bresenham’s line drawing algorithm for all types of slope.",1);
//    glutAddMenuEntry("2.Create and rotate a triangle about the origin and a fixed point.",2);
//    glutAddMenuEntry("3.Draw a color cube and spin it using OpenGL transformation matrices.",3);
//    glutAddMenuEntry("4.Draw a color cube and allow the user to experiment with perspective viewing",4);
    glutAddMenuEntry("2.Clip a lines using Cohen-Sutherland algorithm",5);
    glutAddMenuEntry("3.Draw a simple shaded scene consisting of a tea pot on a table",6);
    glutAddMenuEntry("4.Implement recursively subdivide a tetrahedron to form 3D sierpinski gasket.",7);
    glutAddMenuEntry("5.Develop a  program to animate a flag using Bezier Curve algorithm",8);
    glutAddMenuEntry("6.Develop a program to fill the polygon using scan line algorithm",9);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
}
