//Pooja Goyal
//Student ID:- 109896598
//Project Assignment 3 :- N degree Beizer Curve
#include <string.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#define PI 3.14159
#define MAX_CLICKS 15 //program stop drawing after 15 clicks

using namespace std;
bool WireFrame= false;



long double mouseX=0.0;   // mouse position coordinate  for x-axis
long double mouseY=0.0;   // mouse position coordinate  for y-axis
long double mouseZ= 0.0;  // mouse position coordinate  for z-axis

long double xpos = 0.0;  // beizer curve formation coordinate  for x-axis
long double ypos = 0.0;  // beizer curve formation coordinate  for y-axis
long double zpos = 0.0;  // beizer curve formation coordinate  for z-axis

bool visible = false;           //flag for hide and show points
int mouse_clicks[MAX_CLICKS][3];    //array intialization to store mouse clicks for xyz coordinates
int numbOfClicks = 0;              //number of clicks from mouse possible for one session
int clicks =0;
float Wwidth,Wheight;
float t =0;
static GLint RotateY=0;    //roation along Y-axis coordinate


const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };



/* GLUT callback Handlers */

static void resize(int width, int height)
{
    double Ratio;
    
    Wwidth = (float)width;
    Wheight = (float)height;
   
    Ratio= (double)width /(double)height;
    
    glViewport(0,0,(GLsizei) width,(GLsizei) height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective (45.0f,Ratio,0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

//Recursive function to calculate factorial

long double fact(double n)
{
    if (n<=1)
        return(1);
    else
        n=n*fact(n-1);
    return n;
    
}
//Recursive function to calculate Binomial Coefficient

long double binomial(double n,double i)
{
    long double bin_coff;
    bin_coff = fact(n) / (fact(i)*fact(n-i));
    return bin_coff;
    
    
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    gluLookAt(0,0,10,0.0,0.0,0.0,0.0,1.0,100.0);
    
    if(WireFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);        //Draw Our Mesh In Wireframe Mesh
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);        //Toggle WIRE FRAME
    
// your code here
    if(visible){     //toggle between hide/show control points
        //Draw Points
        glTranslatef(0,0,-3);
        glRotatef(RotateY,0,1,0);
      
        glPointSize(5);
        glBegin(GL_POINTS);
        
         glColor3f(1.0f, 0.0f, 1.0f);
     //loop for vertex points for x,y,z stored points
        for(int j=0;j<numbOfClicks;j++){
            glVertex3f(mouse_clicks[j][0],mouse_clicks[j][1],mouse_clicks[j][2]);
            }
       
        
        glEnd();
    }
    // j for loop ends
    if(numbOfClicks >=3)  //draw curve when 3 or more points on the window
    {
        for (int k =3; k <=clicks; k++) {
            
            numbOfClicks = k;
              for(t=0;t<1;t=t+0.0003)   {  //formation of curve line
           
                   for(int i=0;i<numbOfClicks;i++) {  //get x,y,z points position to make the curve using binomial recursive function
                            xpos = xpos + binomial((double)(numbOfClicks - 1), (double)i) *
                                   pow(t, (double)i) * pow((1 - t), (numbOfClicks - 1 - i)) * mouse_clicks[i][0];
                       
                            ypos = ypos + binomial((double)(numbOfClicks - 1), (double)i) *
                                   pow(t, (double)i) * pow((1 - t), (numbOfClicks - 1 - i)) * mouse_clicks[i][1];
                       
                            zpos = zpos + binomial((double)(numbOfClicks - 1), (double)i) *
                                   pow(t, (double)i) * pow((1 - t), (numbOfClicks - 1 - i)) * mouse_clicks[i][2];
                    
                   } //for loop i ends
               
                    glPointSize(2);
                    glBegin(GL_POINTS);
                    glColor3f(0.0,.0,1.0);
                    glVertex3f(xpos,ypos,zpos);
                    glEnd();
                  
                    xpos=0; ypos=0; zpos =0;
                  
                
           } //for loop t ends
          
    }  // for loop k ends
        
} // if statement ends
    glutSwapBuffers();
    
}
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 32:
            numbOfClicks=0;  //Reset points
            glutPostRedisplay();
            break;
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'w':
            WireFrame =!WireFrame;
            break;
            }
    
}

void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
            case GLUT_KEY_LEFT: // Clockwise rotation over Y-axis
                RotateY =((int)RotateY +5)%360;
                RotateY =((int)RotateY +5)%360;
                break;
            case GLUT_KEY_RIGHT:  // Counter-Clockwise rotation over Y-axis
                RotateY =((int)RotateY -5)%360;
                RotateY =((int)RotateY -5)%360;
                break;
            
    }
    glutPostRedisplay();
    
}

static void idle(void)

{
    glutPostRedisplay();
    
}

void mouse(int btn, int state, int x, int y){
    
    float scale = 54*(Wwidth/Wheight);
   
    //  printf(" original %d %d \n", x,y);
    switch(btn){
            case GLUT_LEFT_BUTTON:
           
            if(state==GLUT_DOWN){
                // get new mouse coordinates for x,y
                // use scale to match right
                 visible = true;
                if(numbOfClicks <= MAX_CLICKS)
                    {
                    mouseX = (x - (Wwidth/2))/scale;   // Get the mouse x  coordinate, and translate based on origin.
                    mouseY = ((Wheight/2) - y)/scale; //  Get the mouse y coordinate, and translate based on origin.
                    mouseZ = (-3.0 + numbOfClicks * 0.175)/scale;   // Get the mouse z coordinate,starting at 3 increment 0.2 with each click
                  
                        
                    }
            
                
                mouse_clicks[clicks][0] = mouseX;    //store mouse clicked points to mouse_clicks array for x coordinates
                mouse_clicks[clicks][1] = mouseY;   //store mouse clicked points to mouse_clicks array for y coordinates
                mouse_clicks[clicks][2] = mouseZ;   //store mouse clicked points to mouse_clicks array for z coordinates
                
                clicks++;
                numbOfClicks++;
                t=0;
               
               
                
            }
            
            break;
            
     case GLUT_MIDDLE_BUTTON:
         if(state==GLUT_DOWN){
             numbOfClicks = 0;  //Reset points
             }
        break;
     case GLUT_RIGHT_BUTTON:
            if(state==GLUT_DOWN){
               visible = false;    //toggle between show/hide
            }
        break;
            }
glutPostRedisplay();
};

static void init(void)

{
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);                 // assign a color you like
    
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    
}

/* Program entry point */
int main(int argc, char *argv[])

{
    glutInit(&argc, argv);
    
    glutInitWindowSize(800,600);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutCreateWindow("Project Assignment 3");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);
    
    glutIdleFunc(idle);
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
    
}

