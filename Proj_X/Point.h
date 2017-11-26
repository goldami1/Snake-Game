#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h"

#define		UP						1
#define		DOWN					-1
#define		LEFT					2
#define		RIGHT					-2

using namespace std;

class Point {
	int x = 1, y = 1;
public:
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	void set(int _x, int _y) {
		x = _x;
		y = _y;
	}
	void draw(char ch) {
		gotoxy(x, y);
		cout << ch;
		cout.flush();
	}
	void move();
	Point(int _x = 0, int _y = 0) :x(_x), y(_y) {}
	void move(int direction);
	Point next(int direction) {
		Point next = *this;
		next.move(direction);
		return next;
	}
		bool operator==(const Point& _point) {return (this->x == _point.getX() && this->getY() == _point.getY());}
		const Point& operator=(const Point src) { set(src.getX(), src.getY());  return *this; }
};

#endif