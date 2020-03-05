#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "structs.h"

float calcSlope(Triangle tri, int i1, int i2) {
	return ((float)(tri.points[i1].y - tri.points[i2].y)) / 
	((float) (tri.points[i1].x - tri.points[i2].x));
}

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
 */
void generateImage(Color* pixels, int w, int h, int N, Triangle* triangles) {
	
	//Color c = color_c(255, 0, 0, 255);
	//Triangle triangle = triangle_c(-300+w/2,300+h/2, 300+w/2,300+h/2, 70+w/2, -100+h/2, c);
	//Triangle triangle = triangles[0];
	
	printf("W: %d, H: %d\n", w, h);
	
	//printf("Triangle: %d,%d\n%d,%d\n%d,%d\n",triangle.points[0].x,triangle.points[0].y,triangle.points[1].x,triangle.points[1].y,triangle.points[2].x,triangle.points[2].y);
	
	for (int y = 0; y < h; y++) {
		//loop through all triangles
		//TODO: Add array of triangles
		for (int triN = 0; triN < N; triN++) {
			Triangle triangle = triangles[triN];
			if (lineIntersectsTriangle(y, triangle)) {
				//Determine intersection points:
				int numIntersections = 0;
				float xIntercepts[3];
				if (numBetween(y, triangle.points[0].y, triangle.points[1].y)) {
					float slope = calcSlope(triangle, 0, 1);
					xIntercepts[numIntersections] = ((float)(y-triangle.points[0].y))/slope + ((float)triangle.points[0].x);
					numIntersections++;
				}
				if (numBetween(y, triangle.points[1].y, triangle.points[2].y)) {
					float slope = calcSlope(triangle, 1, 2);
					xIntercepts[numIntersections] = ((float)(y-triangle.points[1].y))/slope + ((float)triangle.points[1].x);
					numIntersections++;
				}
				if (numBetween(y, triangle.points[0].y, triangle.points[2].y)) {
					float slope = calcSlope(triangle, 0, 2);
					xIntercepts[numIntersections] = ((float)(y-triangle.points[0].y))/slope + ((float)triangle.points[0].x);
					numIntersections++;
				}
				
				if(numIntersections == 2) {
					//Fill inbetween the two points
					if (xIntercepts[0] < xIntercepts[1]) {
						int x;
						int low = (int) xIntercepts[0];
						int high = (int) xIntercepts[1];
						for (x= low; x <= high; x++) {
							if ( x >= 0 && x < w) {
								pixels[x + y*w] = triangle.color;
							}
						}
					}
					else {
						int x;
						int low = (int) xIntercepts[1];
						int high = (int) xIntercepts[0];
						for (x=low; x < high; x++) {
							if ( x >= 0 && x < w) {
								pixels[x + y*w] = triangle.color;
							}
						}
					}	
				} else if (numIntersections == 3) {
				}
			}
		}
	}
}
