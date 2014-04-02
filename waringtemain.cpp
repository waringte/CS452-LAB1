//g++ error.cpp -lglut -lGL -lGLEW -g
#include "initShaders.h"
using namespace std;
int counter=0;

GLuint vaoID, vboID;

GLfloat tri[]={
-0.5f,-0.433f,0.0f,
0.5f,-0.433f,0.0f,
0.0f,0.433f,0.0f};

GLfloat sqr[]={
-0.5f,-0.5f,0.0f,
-0.5f,0.5f,0.0f,
0.5f,0.5f,0.0f,
0.5f,-0.5f,0.0f};
GLfloat pnt[]={
-0.5f,-0.769f,0.0f,
0.5f,-0.769f,0.0f,
.809f,0.181f,0.0f,
0.0f,.769f,0.0f,
-0.809f,0.181f,0.0f};

GLubyte indTri[3]={0,1,2};
GLubyte indSqr[4]={0,1,2,3};
GLubyte indPnt[5]={0,1,2,3,4};

void triangle(){
  glClear(GL_COLOR_BUFFER_BIT);
  
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);

  glGenBuffers(1, &vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(tri), tri, GL_STATIC_DRAW);

 ShaderInfo shaders[]={
  { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
  { GL_NONE , NULL}
  };

  initShaders(shaders);
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

  glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_BYTE, indTri);
  glFlush();
}

void square(){
  glClear(GL_COLOR_BUFFER_BIT);

  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);

  glGenBuffers(1, &vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(sqr), sqr, GL_STATIC_DRAW);

 ShaderInfo shaders[]={
  { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
  { GL_NONE , NULL}
  };

  initShaders(shaders);
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
  
  glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, indSqr);
  glDisableVertexAttribArray(0);
  glFlush();
}

void pentagon(){
  glClear(GL_COLOR_BUFFER_BIT);

  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);

  glGenBuffers(1, &vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(pnt), pnt, GL_STATIC_DRAW);

 ShaderInfo shaders[]={
  { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
  { GL_NONE , NULL}
  };

  initShaders(shaders);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

  glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, indPnt);
  glDisableVertexAttribArray(0);
  glFlush();
}


void drawscene(){
  switch(counter%3){
    case 0:
      glutDisplayFunc(triangle);
      glutPostRedisplay();
      break;
    case 1:
      glutDisplayFunc(square);
      glutPostRedisplay();
      break;
    case 2:
      glutDisplayFunc(pentagon);
      glutPostRedisplay();
      break;

  }
}
void mousepress(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    exit(0);
  else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
    counter++;
    drawscene();
  }
}

void idle(void){
  glutPostRedisplay();
}

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutCreateWindow("Shapes");

  glewExperimental=GL_TRUE;
  if(glewInit()){
    fprintf(stderr, "Unable to initalize GLEW");
    exit(EXIT_FAILURE);
  }
  
  glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE);

  const GLubyte* version=glGetString(GL_SHADING_LANGUAGE_VERSION);
  fprintf(stderr,"Opengl glsl version %s\n", version);

  version=glGetString(GL_VERSION);
  fprintf(stderr,"Opengl version %s\n", version);

  glutDisplayFunc(drawscene);
  glutMouseFunc(mousepress);
  glutMainLoop();
  return 0;
}
