//Pooja Goyal
//Student ID: 109896598
//Project 5  Texture Mapping & Loading

#include "SOIL.h"
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
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;



bool WireFrame= false;

GLuint tex[6]; // Texture pointer
//Rotation of Skybox
float SRotateX =0;
float SRotateY =0;
float SRotateZ =0;
//Rotation of cube/ateneam
float RotateX =0;
float RotateY =0;
float RotateZ =0;

float translate_z =-1;
float Wwidth;
float Wheight;


const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
//draw points for reading file
struct Draw {

    float x;
    float y;
    float z;

};

Draw vertex[256];
Draw Normal[256];
int ind[12][6];
GLfloat z = 0.0, t;

void getvertices(char* filename)
{
    ifstream file;
    file.open(filename);
    string str;
    while(!file.eof()) //while we are still in the file
    {
        getline(file,str); //move one line down
        if(str[0] == 'v' && str[1] == ' ') break; //if we have a vertex line, stop
    }
    int v = 0;
    while(str[0] == 'v' && str[1] == ' ') {
    cout<<str<<endl;
        int i = 0;
        while(true){
            while(str[i] == ' ' )
            {
                i++; //move a space over
            }
            i++;
            i++;
            int j = i, k = i;
            while(str[i] != ' ') {
                i++;
                k = i;
            }
            vertex[v].x = atof(str.substr(j, k-j).c_str());

            //moving on to the y coord

            while(str[i] == ' ' ) {
                i++;
            }

            int q = i, w = i;
            while(str[i] != ' ' ) {
                i++;
                w = i;
            }
            vertex[v].y = atof(str.substr(q, w-q).c_str());

            while(str[i] == ' ' ) {
                i++;
            }

            int a = i, s = i;
            while(str[i] != ' ' ) {
                i++;
                s = i;
            }
            vertex[v].z = atof(str.substr(a, s-a).c_str());

            break;
        }
        cout<<vertex[v].x<<"  "<< vertex[v].y<<"  "<< vertex[v].z<<endl;
        v++;
        getline(file, str);
    }
}

void getNormals(char* filename)
{
    ifstream file;
    file.open(filename);
    string str;
    while(!file.eof()) //while we are still in the file
    {
        getline(file,str); //move one line down
        if(str[0] == 'v' && str[1] == 'n') break; //if we have a vertex line, stop
    }
    int v = 0;
    while(str[0] == 'v' && str[1] == 'n') {
    cout<<str<<endl;
        int i = 0;
        while(true){
            while(str[i] == ' ' )
            {
                i++; //move a space over
            }
            i++;
            i++;
            i++;
            int j = i, k = i;
            while(str[i] != ' ') {
                i++;
                k = i;
            }
            Normal[v].x = atof(str.substr(j, k-j).c_str());

            //moving on to the y coord

            while(str[i] == ' ' ) {
                i++;
            }

            int q = i, w = i;
            while(str[i] != ' ' ) {
                i++;
                w = i;
            }
            Normal[v].y = atof(str.substr(q, w-q).c_str());

            while(str[i] == ' ' ) {
                i++;
            }

            int a = i, s = i;
            while(str[i] != ' ' ) {
                i++;
                s = i;
            }
            Normal[v].z = atof(str.substr(a, s-a).c_str());

            break;
        }
        cout<<Normal[v].x<<"  "<< Normal[v].y<<"  "<< Normal[v].z<<endl;
        v++;

        getline(file, str);
    }
}

void getIndices(char* filename)
{
    ifstream file;
    file.open(filename);
    string str;
    while(!file.eof()) //while we are still in the file
    {
        getline(file,str); //move one line down
        if(str[0] == 'f' && str[1] == ' ') break; //if we have a vertex line, stop
    }
    int v = 0,indX=0;
    while(str[0] == 'f' && str[1] == ' ') {
    cout<<str<<endl;
        int i = 0,indY=0;
        while(true){
            while(str[i] == ' ' )
            {
                i++; //move a space over
            }
            i++;
            i++;
            int j = i, k = i;
            while(str[i] != ' ') {
                i++;
                k = i;
            }
            //cout<<str[j]<<"  "<<str[i-1]<<endl;
            ind[indX][indY] = atof(str.substr(j, j+1).c_str());
            indY++;
            ind[indX][indY] = atof(str.substr(i-1, i).c_str());
            indY++;
            //vertex[v].x = atof(str.substr(j, k-j).c_str());

            //moving on to the y coord

            while(str[i] == ' ' ) {
                i++;
            }

            int q = i, w = i;
            while(str[i] != ' ' ) {
                i++;
                w = i;
            }
            ind[indX][indY] = atof(str.substr(q, q+1).c_str());
            indY++;
            ind[indX][indY] = atof(str.substr(i-1, i).c_str());
            indY++;


            while(str[i] == ' ' ) {
                i++;
            }

            int a = i, s = i;
            while(str[i] != '\0' ) {
                i++;
                s = i;
            }
            ind[indX][indY] = atof(str.substr(a, a+1).c_str());
            indY++;
            ind[indX][indY] = atof(str.substr(i-1, i).c_str());
            break;
        }
        indX++;
        getline(file, str);
    }
    for(int ll =0 ;ll<12;ll++){
        for(int mm=0;mm<6;mm++){
            cout<<ind[ll][mm]<<"  ";
        }
        cout<<endl;
    }
}


/* GLUT callback Handlers */
static void resize(int width, int height)
{
    double Ratio = (double)width/(double)height;

    glViewport(0,0,(GLsizei) width,(GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (45.0f,Ratio,0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,10,0.0,0.0,0.0,0.0,1.0,0.0);

    if(WireFrame)
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//Draw Our Mesh In Wireframe Mesh
else
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//Toggle WIRE FRAME

    // your code here
    glPushMatrix();
      glColor3f(1.0, 1.0, 1.0);
    glTranslated(0,0,translate_z);
    glRotated(SRotateX,1,0,0);
    glRotated(SRotateY,0,1,0);
    glRotated(SRotateZ,0,0,1);

   glScalef(20.0, 10.0, 20.0);

    //change y values in front,back face

    // Front Face
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glBegin(GL_QUADS);
     glNormal3f(0.0f,0.1f,0.1f);
      glBindTexture(GL_TEXTURE_2D, tex[0]);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  -1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  -1.0f,  1.0f);  // Top Left Of The Texture and Quad
    glEnd();

     // Back Face
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, +1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  -1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  -1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, +1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    glEnd();

    //change x on top and bottom
    // Top Face
    glBindTexture(GL_TEXTURE_2D, tex[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glEnd();


    // Bottom Face
    glBindTexture(GL_TEXTURE_2D, tex[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( -1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( -1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glEnd();

    //change x, y, z on right and left
    // Right face
    glBindTexture(GL_TEXTURE_2D, tex[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.0f, 1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.0f,  -1.0f, 1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( -1.0f,  -1.0f,  -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( -1.0f, 1.0f,  -1.0f);  // Bottom Left Of The Texture and Quad
    glEnd();

    // Left Face
    glBindTexture(GL_TEXTURE_2D, tex[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, +1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, +1.0f,  -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,  -1.0f,  -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,  -1.0f, 1.0f);  // Top Left Of The Texture and Quad
    glEnd();
    glPopMatrix();
       glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
// images are 2D arrays of pixels, bound to the GL_TEXTURE_2D target.

    glPushMatrix(); // Pushing the matrix.
  //  glColor3f(1.0,1.0,1.0);
 glTranslated(0.0,0.0,translate_z); // This is used for translating forward and backward for Zooming In and Out.
    glRotated(RotateX,1,0,0); // This is used for rotating Up/Down with respect to X-axis.
    glRotated(RotateY,0,1,0); // This is used for rotating Left/Right with respect to Y-axis.

     for(int k=0;k<12;k++){

            glBegin(GL_TRIANGLES);


       glColor3f(vertex[ind[k][0]-1].x,vertex[ind[k][0]-1].y,vertex[ind[k][0]-1].z);
        glNormal3f(Normal[ind[k][1]-1].x,Normal[ind[k][1]-1].y,Normal[ind[k][1]-1].z);
        glVertex3f(vertex[ind[k][0]-1].x,vertex[ind[k][0]-1].y,vertex[ind[k][0]-1].z);

       glColor3f(vertex[ind[k][2]-1].x,vertex[ind[k][2]-1].y,vertex[ind[k][2]-1].z);
        glNormal3f(Normal[ind[k][3]-1].x,Normal[ind[k][3]-1].y,Normal[ind[k][3]-1].z);
        glVertex3f(vertex[ind[k][2]-1].x,vertex[ind[k][2]-1].y,vertex[ind[k][2]-1].z);

        glColor3f(vertex[ind[k][4]-1].x,vertex[ind[k][4]-1].y,vertex[ind[k][4]-1].z);
        glNormal3f(Normal[ind[k][5]-1].x,Normal[ind[k][5]-1].y,Normal[ind[k][5]-1].z);
        glVertex3f(vertex[ind[k][4]-1].x,vertex[ind[k][4]-1].y,vertex[ind[k][4]-1].z);

        glTranslated(3.0,0.0,0.0);
    }
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {   case 'a':
 translate_z += (float) 1.0f;
break;
 case 'z':
 translate_z -= (float) 1.0f;
break;
    }
}

void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
     case GLUT_KEY_END:
 translate_z += (float) 1.0f;
break;
case GLUT_KEY_HOME:
 translate_z -= (float) 1.0f;
break;
    case GLUT_KEY_UP:	/* Clockwise rotation over X */
RotateX = ((int)RotateX +5)%360;
break;
case GLUT_KEY_DOWN:	/* Counter Clockwise rotation over X */
RotateX = ((int)RotateX -5)%360;
 break;
case GLUT_KEY_LEFT:	/* Clockwise rotation over Y */
    RotateY =((int)RotateY +5)%360;
break;
case GLUT_KEY_RIGHT:
RotateY = ((int)RotateY -5)%360;/* Counter Clockwise rotation over Y */
break;

   }
  glutPostRedisplay();
}
void mouseMotion(int x, int y)

{

    static float prevX = 0.0;

    static float prevY = 0.0;

    prevX = (float)x - prevX;

    prevY = (float)y - prevY;

    if((abs((int)prevX)>15)||(abs((int)prevY)>15))

    {

        prevX = (float)x;

        prevY = (float)y;

        return;

    }

    SRotateY = ((int)SRotateY + (int)prevX)%360;   //rotation of skybox on mouse cursor

    SRotateX = ((int)SRotateX + (int)prevY)%360;

}



static void idle(void)
{
    glutPostRedisplay();
}

void textureloader(string imagelink, GLuint t){
     glBindTexture(GL_TEXTURE_2D, t); // images are 2D arrays of pixels, bound to the GL_TEXTURE_2D target.

     int width, height; // width & height for the image reader
     unsigned char* image;

     image = SOIL_load_image(imagelink.c_str() , &width, &height, 0, SOIL_LOAD_RGB);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    // binding image data
     SOIL_free_image_data(image);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
};

static void init(void)
{
    AllocConsole();
    freopen( "CON", "wt", stdout );
    freopen( "CON", "wt", stderr );

   getvertices("cube.obj");
    getNormals("cube.obj");
    getIndices("cube.obj");
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
t = 0.0;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(6, tex);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
//texture loading 6 images n my skybox inside
    textureloader("/Users/poojagoyal/Desktop/proj5/images/front.jpg", tex[0]);
   textureloader("/Users/poojagoyal/Desktop/proj5/images/back.jpg", tex[1]);
    textureloader("/Users/poojagoyal/Desktop/proj5/images/top.jpg", tex[2]);
    textureloader("/Users/poojagoyal/Desktop/proj5/images/bottom.jpg", tex[3]);
    textureloader("/Users/poojagoyal/Desktop/proj5/images/right.jpg", tex[4]);
    textureloader("/Users/poojagoyal/Desktop/proj5/images/left.jpg", tex[5]);
}


/* Program entry point */

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);
glutMotionFunc(mouseMotion);   //mouse motion function
    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
