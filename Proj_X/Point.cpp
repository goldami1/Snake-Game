#include "Point.h"

void Point::move() {
	int dir = rand() % 4;
	move(dir);
}

void Point::move(int dir) {
	switch (dir) {
	case UP: // UP// 0
		--y;
		if (y < 4) {
			y = 23;
		}
		break;
	case DOWN: // DOWN // 1
		++y;
		if (y > 23) {
			y = 4;
		}
		break;
	case LEFT: // LEFT // 2
		--x;
		if (x < 0) {
			x = 79;
		}
		break;
	case RIGHT: // RIGHT //3
		++x;
		if (x > 79) {
			x = 0;
		}
		break;
	}
}