#ifndef _NUMBER_H_
#define _NUMBER_H_

#include <cstring>
#include "Point.h"

class TheSnakesGame;

class Number {
	int len = -1, val = -1;
	Point *body = nullptr;
	TheSnakesGame* theGame = nullptr;

	int getNumsRange();
	void getValidXYCoord(int *xCoord, int *yCoord);
	
	

public:
	Point* getNumberLoc();	//memory allocation done - don't forget to delete after use of product
	int getNumLen()	{ return getNumLen(val); }
	void setGame(TheSnakesGame* _theGame)	{theGame = _theGame;}
	int getNumVal()const { return val;}
	void printNumber();
	void deleteNumber();
	Point getLoc() { if (body != nullptr) return body[0]; else return Point(-1, -1); }
	bool doesIncludeThePoint(const Point& p);
	void setNumVal(int _val) { val= _val; }
	int getNumLen(int num);

	Number();

	void setNumber();
	void setnumberPart2();
	void Number::set(Number src);


	
};

#endif