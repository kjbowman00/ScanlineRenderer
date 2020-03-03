typedef struct {
  int x;
  int y;
} Point;

Point point_c(int x, int y);

typedef struct {
	Point* points;
} Triangle;

Triangle triangle_c(int x1, int y1, int x2, int y2, int x3, int y3);
