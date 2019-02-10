//Pooja Goyal

//CSCI 272 - 2D ANIMATION

//109896598


#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>

#define PI 3.14159
#include "SOIL.h"

using namespace std;

bool WireFrame= false;



const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

float Wwidth,Wheight;
GLuint tex;    // Texturemapping variable


float Xmin=0;  //minimum x-coordinate for the sprite sheet
float Xmax=0.1666;  //maximum x-coordinate for the sprite sheet when divide into 6 frames
float Ymin=0;  //minimum y-coordinate for the sprite sheet
float Ymax=1;  //maximum y-coordinate for the sprite sheet



float zoomS;     //zoom in and out for the frame


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


gluPerspective (45.0f,Ratio,0.1f, 1000.0f);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

 }


 void textureLoader(char* fileName, GLuint &handle)
{
    int width, height; // width & height for the image reader
     unsigned char* image;


     glBindTexture(GL_TEXTURE_2D, handle); // images are 2D arrays of pixels, bound to the GL_TEXTURE_2D target.

      image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

     if(!image){cout<<"Image file not found"<<endl;}
// binding image data
     SOIL_free_image_data(image);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);

}


static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,10,0.0,0.0,0.0,0.0,1.0,100.0);

    if(WireFrame)
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//Draw Our Mesh In Wireframe Mesh
else
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//Toggle WIRE FRAME



    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0,0,zoomS);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_POLYGON);
    // Front Face
    glTexCoord2f(Xmin, Ymin); glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(Xmax, Ymin); glVertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(Xmax, Ymax); glVertex3f( 1.0f, -1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(Xmin, Ymax); glVertex3f(-1.0f, -1.0f,  1.0f);  // Top Left Of The Texture and Quad
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}



static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
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

        case GLUT_KEY_UP:	//zoom in the animation with 0.5 increment
             zoomS=zoomS+0.5;
         break;
        case GLUT_KEY_DOWN:	//zoom out of the animation with 0.5 decrement
             zoomS=zoomS-0.5;
         break;
        case GLUT_KEY_LEFT:	//run backward the animation frames
            Xmin = Xmin- (0.1666);
            Xmax = Xmax- (0.1666);
        break;
        case GLUT_KEY_RIGHT:                //run forward the animation frames
             Xmin = Xmin+ (0.1666);
             Xmax = Xmax+ (0.1666);
        break;



   }
  glutPostRedisplay();
}

static void idle(void)
{
    // Use parametric equation with t increment for xpos and y pos

     glutPostRedisplay();
}


void mouse(int btn, int state, int x, int y){

     switch(btn){
        case GLUT_LEFT_BUTTON:

        if(state==GLUT_DOWN){

               // get new mouse coordinates for x,y
               // use scale to match right
            }
            break;
    }

     glutPostRedisplay();
};


static void init(void)
{

    glClearColor(0.0, 0.0, 0.25, 0.0);                 // assign a color you like

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

     glGenTextures(1, &tex);
     glEnable(GL_TEXTURE_2D);
    textureLoader("/Users/poojagoyal/Desktop/proj4/images/fe.png", tex);  //load the image for texture wrapping around square

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     zoomS = -1;
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Project Assignment 3-II");
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
