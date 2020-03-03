#include<stdio.h>
#include<GL/glut.h>
#include"structs.h"

#define WIDTH 1560
#define HEIGHT 840

int* pixels;
  
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
    
    for (y = 0; y < WIDTH; y++) {
		for (x = 0; x < HEIGHT; x++) {
			
		}
	}
    
    
    
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
    glutInitWindowSize(1366, 768); 
    glutInitWindowPosition(0, 0); 
      
    // Giving name to window 
    glutCreateWindow("Scanline Renderer"); 
    myInit(); 
      
    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;
} 
