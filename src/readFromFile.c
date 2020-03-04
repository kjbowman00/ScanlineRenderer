#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

Triangle* getTriangles(char* fileName, int N) {
	FILE* ptr = fopen(fileName,"r"); 
    if (ptr==NULL) 
    { 
        printf("Triangle File Not Found\n");
        return null; 
    } 
    
	scanf("%d\n", &N);
	Triangle* triangles = calloc(N, sizeof(Triangle));
}
