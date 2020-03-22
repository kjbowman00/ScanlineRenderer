#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "structs.h"

Texture readTexture(char* fileName);
void map(int sL, int dL, Color* source, Color* destination);
Texture textureMap(Texture source, int nW, int nH);

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
 * Calculates triangles width and height
 **/
void triWH(Triangle tri, int* w, int* h) {
	int h1 = abs(tri.points[0].y - tri.points[1].y);
	int h2 = abs(tri.points[0].y - tri.points[2].y);
	int h3 = abs(tri.points[1].y - tri.points[2].y);
	int bigH = h1;
	if (h2 > bigH) bigH = h2;
	if (h3 > bigH) bigH = h3;
	
	int w1 = abs(tri.points[0].x - tri.points[1].x);
	int w2 = abs(tri.points[0].x - tri.points[2].x);
	int w3 = abs(tri.points[1].x - tri.points[2].x);
	int bigW = w1;
	if (w2 > bigW) bigW = w2;
	if (w3 > bigW) bigW = w3;
	*w = bigW;
	*h = bigH;
}

/**
 * Fills a pixel array based on triangles position
 */
void generateImage(Color* pixels, int w, int h, int N, Triangle* triangles) {
	Texture myTexture = readTexture("testTexture.txt");
	
	//Used to track where in each texture the triangle is at
	int* triangleIntersectionCounter = (int*) calloc(N, sizeof(int));
	for (int y = 0; y < h; y++) {
		//loop through all triangles
		//TODO: Add array of triangles
		for (int triN = 0; triN < N; triN++) {
			Triangle triangle = triangles[triN];
			//Map myTexture to the size of the triangle
			int tW, tH;
			triWH(triangle, &tW, &tH);
			Texture mapT = textureMap(myTexture, tW, tH);
			
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
				
				//Determine left intersection and right intersection
				if (numIntersections == 2) {
					if (xIntercepts[0] > xIntercepts[1]) {
						int temp = xIntercepts[0];
						xIntercepts[0] = xIntercepts[1];
						xIntercepts[1] = temp;
					}
				}
				else if (numIntersections == 3) {
					int max = xIntercepts[0];
					int min = xIntercepts[0];
					for (int i = 1; i < 3; i++) {
						if (xIntercepts[i] > max) {
							max = xIntercepts[i];
						}
						if (xIntercepts[i] < min) {
							min = xIntercepts[i];
						}
					}
					xIntercepts[0] = min;
					xIntercepts[1] = max;
				}
				
				//Fill inbetween the two points
				if (numIntersections >= 2) {
					int x;
					int low = (int) xIntercepts[0];
					int high = (int) xIntercepts[1];
					
					//Generate pixels from texture
					int dL = high-low+1;
					Color cArray[dL];
					map(mapT.w, dL, mapT.colors + triangleIntersectionCounter[triN]*mapT.w, cArray);
					
					int count = 0;
					for (x= low; x <= high; x++) {
						if ( x >= 0 && x < w) {
							pixels[x + y*w] = cArray[count];
							count++;
						}
					}
				}
				triangleIntersectionCounter[triN] += 1;
			}
			texture_d(mapT);
		}
	}
}
