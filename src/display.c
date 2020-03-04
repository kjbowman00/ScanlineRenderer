#include <stdio.h>
#include <GL/glut.h>
#include "structs.h"

#define WIDTH 500
#define HEIGHT 500

int* pixels;

void generateImage(int* pixels, int width, int height);
  
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
			if (pixels[x + WIDTH*y] == 1) {
				glVertex2i(x-WIDTH/2,y-HEIGHT/2);
			}
		}
	}
    
    
    //Draw 3 test points
    glColor3f(0,1,0);
    glVertex2i(10,10);
    glVertex2i(-50,-50);
    glVertex2i(50,-80);
    
    glColor3f(0,0,1);
    glVertex2i(0,0);
    
    
    glEnd(); 
    glFlush(); 
} 
  
int main (int argc, char** argv) 
{ 
	//GENERATE IMAGE
	pixels = (int*) calloc(WIDTH*HEIGHT, sizeof(int));
	if (pixels == NULL) {
		printf("pixels array not allocated\n");
		return 0;
	}
	generateImage(pixels, WIDTH, HEIGHT);
	
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
