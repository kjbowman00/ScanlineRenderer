#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structs.h"

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

void grabColumn(Texture source, Color* dest, int colN) {
	int i;
	int len = source.h;
	for (i = 0; i < len; i++) {
		dest[i] = source.colors[len*i + colN];
	}
}

void fillColumn(Color* source, Texture dest, int colN) {
	int i;
	int len = dest.h;
	for (i = 0; i < len; i++) {
		dest.colors[len*i + colN] = source[i];
	}
}

/**
 * maps a texture to a new desired width and height
 **/
Texture textureMap(Texture source, int nW, int nH) {
	Texture heightScaled = texture_c(source.w, nH);
	
	int i;
	//Loop through the columns
	for (i = 0; i < nW; i++) {
		//Grab the old column
		Color oldCol[source.h];
		grabColumn(source, oldCol, i);
		
		//Map it to the new column height
		Color newCol[nH];
		map(source.h, nH, oldCol, newCol);
		
		//Insert it into the texture
		fillColumn(newCol, heightScaled, i);
	}
	return heightScaled;
}
