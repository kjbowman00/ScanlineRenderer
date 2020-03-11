#include <stdlib.h>
#include <stdio.h>
#include <structs.h>
#include <math.h>

/**
 * Maps an array of colors to another array. Will scale up
 * or down depending on length.
 * sL is length of source and dL is length of destination color array
 **/
void map(int sL, int dL, Color* source, Color* destination) {
	float m = -1 * ((float) sL) / ((float) dL);
	
	int i;
	for (i = 0; i < dL; i++) {
		int j = round(m * ((float) i) + ((float) sL));
		destination[i] = source[j];
	}
}
