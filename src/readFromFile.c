#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

Triangle* getTriangles(char* fileName, int* N, int w, int h) {
	FILE* ptr = fopen(fileName,"r"); 
    if (ptr==NULL) 
    { 
        printf("Triangle File Not Found\n");
        return NULL; 
    } 
    
	fscanf(ptr,"%d\n", N);
	Triangle* triangles = calloc(*N, sizeof(Triangle));
	
	for (int i = 0; i < *N; i++) {
		int x1,y1, x2,y2, x3,y3, r,g,b,a;
		fscanf(ptr, "%d %d %d %d %d %d %d %d %d %d\n", &x1, &y1, &x2,&y2, &x3,&y3, &r,&g,&b,&a);
		Color c = color_c(r,g,b,a);
		Triangle t = triangle_c(x1 + w/2,y1+h/2, x2+w/2,y2+h/2, x3+w/2,y3+h/2, c);
		triangles[i] = t;
	}
	fclose(ptr);
	return triangles;
}
