#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "structs.h"

/**
 * Checks if a number is between two numbers.
 * Order of bounds is not important
 */
bool numBetween(int y, int b1, int b2) {
	if (b1 < b2) {
		return y >= b1 && y <= b2;
	}
	else {
		return y <= b1 && y >= b2;
	}
}

/**
 * Checks if a y line intersects a triangle
 */
bool lineIntersectsTriangle(int y, Triangle tri) {
	return numBetween(y, tri.points[0].y, tri.points[1].y) ||
			numBetween(y, tri.points[1].y, tri.points[2].y) ||
			numBetween(y, tri.points[0].y, tri.points[2].y);
	//TODO: may only need to check two edges for efficiency
}

/**
 * Fills a pixel array based on triangles position
 * 
 */
void generateImage(int* pixels, int w, int h) {
	
	Triangle triangle = triangle_c(50,50, 200,200, 150, 250);
	
	for (int y = 0; y < h; y++) {
		//loop through all triangles
		//TODO: Add array of triangles
		if (lineIntersectsTriangle(y, triangle)) {
			for (int i = 0; i < w; i++) {
				pixels[i + y*w] = 1;
			}
		}
	}
}
