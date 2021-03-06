#include "structs.h"
#include <stdlib.h>
Point point_c(int x, int y) {
	Point point;
	point.x = x;
	point.y = y;
	return point;
}

Triangle triangle_c(int x1, int y1, int x2, int y2, int x3, int y3, Color color) {
	Triangle t;
	t.points[0] = point_c(x1,y1);
	t.points[1] = point_c(x2,y2);
	t.points[2] = point_c(x3,y3);
	t.color = color;
	return t;
}

Color color_c(int r, int g, int b, int a) {
	Color c;
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return c;
}

Texture texture_c(int w, int h) {
	Texture t;
	t.w = w;
	t.h = h;
	t.colors = (Color*) calloc(w * h, sizeof(Color));
	return t;
}

void texture_d(Texture t) {
	free(t.colors);
}
