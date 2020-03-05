#include <stdio.h>
#include <GL/glut.h>
#include "structs.h"

#define WIDTH 500
#define HEIGHT 500

Color* pixels;

void generateImage(Color* pixels, int width, int height, int N, Triangle* triangles);
Triangle* getTriangles(char* fileName, int* N, int w, int h);
  
// function to initialize 
void myInit (void) 
{ 
    // making background color black as first  
    // 3 arguments all are 0.0 
    glClearColor(0.0, 0.0, 0.0, 1.0); 
      
    // setting window dimension in X- and Y- direction 
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2); 
} 
  
void display (void)  
{ 
    glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_POINTS); 
    int x, y;
    
    glColor3f(1,0,0);
    for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			//if (pixels[x + WIDTH*y] == 1) {
			Color c = pixels[x + WIDTH*y];
			glColor4f( ((float)c.r)/255.0, ((float)c.g)/255.0, ((float)c.b)/255.0, ((float)c.a)/255.0);
			glVertex2i(x-WIDTH/2,y-HEIGHT/2);
			//}
		}
	}
    
    
    glColor3f(0,0,1);
    glVertex2i(0,0);
    
    
    glEnd(); 
    glFlush(); 
} 
  
int main (int argc, char** argv) 
{ 
	//Get Triangles from file
	int N = 0;
	Triangle* triangles = getTriangles("triangles.txt", &N, WIDTH, HEIGHT);
	printf("%d %d %d %d\n",triangles[0].color.r,triangles[0].color.g,triangles[0].color.b,triangles[0].color.a);
	
	//GENERATE IMAGE
	pixels = (Color*) calloc(WIDTH*HEIGHT, sizeof(Color));
	if (pixels == NULL) {
		printf("pixels array not allocated\n");
		return 0;
	}
	generateImage(pixels, WIDTH, HEIGHT, N, triangles);
	
	//PERFORM DISPLAY STUFF
	
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
      
    // giving window size in X- and Y- direction 
    glutInitWindowSize(WIDTH, HEIGHT); 
    glutInitWindowPosition(0, 0); 
      
    // Giving name to window 
    glutCreateWindow("Scanline Renderer"); 
    myInit(); 
      
    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;
} 
