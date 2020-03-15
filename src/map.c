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
	float m = ((float) sL) / ((float) dL);
	int i;
	for (i = 0; i < dL; i++) {
		int j = (int) (m * ((float) i));
		destination[i] = source[j];
	}
}

void grabColumn(Texture source, Color* dest, int colN) {
	int i;
	int len = source.h;
	for (i = 0; i < len; i++) {
		dest[i] = source.colors[source.w*i + colN];
	}
}

void fillColumn(Color* source, Texture dest, int colN) {
	int i;
	int len = dest.h;
	for (i = 0; i < len; i++) {
		dest.colors[dest.w*i + colN] = source[i];
	}
}

void fillRow(Color* source, Texture dest, int rowN) {
	int i;
	for (i = 0; i < dest.w; i++) {
		dest.colors[rowN*dest.w + i] = source[i];
	}
}

/**
 * maps a texture to a new desired width and height
 **/
Texture textureMap(Texture source, int nW, int nH) {
	Texture heightScaled = texture_c(source.w, nH);
	
	int i;
	//Loop through the columns
	for (i = 0; i < source.w; i++) {
		//Grab the old column
		Color oldCol[source.h];
		grabColumn(source, oldCol, i);
		
		//Map it to the new column height
		Color newCol[nH];
		map(source.h, nH, oldCol, newCol);
		
		//Insert it into the texture
		fillColumn(newCol, heightScaled, i);
	}
	
	Texture allScaled = texture_c(nW, nH);
	
	for (i = 0; i < nH; i++) {
		//Grab the old row
		Color* oldRow = heightScaled.colors + i*heightScaled.w;
		
		//Map it to the new row
		Color newRow[nW];
		map(source.w, nW, oldRow, newRow);
		
		//insert it into the texture
		fillRow(newRow, allScaled, i);
	}
	//Deallocate
	texture_d(heightScaled);
	
	return allScaled;
}
