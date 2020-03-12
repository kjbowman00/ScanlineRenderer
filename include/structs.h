#include <stdlib.h>
typedef struct {
  int x;
  int y;
} Point;

Point point_c(int x, int y);

typedef struct {
	int r;
	int g;
	int b;
	int a;
} Color;

typedef struct {
	Point points[3];
	Color color;
} Triangle;

Triangle triangle_c(int x1, int y1, int x2, int y2, int x3, int y3, Color color);
Color color_c(int r, int g, int b, int a);

typedef struct {
	int w, h;
	Color* colors;
} Texture;

Texture texture_c(int w, int h);

