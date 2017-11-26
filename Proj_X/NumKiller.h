#ifndef __NUM_KILLER_H
#define __NUM_KILLER_H
#include "Enemy.h"

struct NumKiller :Enemy {
	
private:
	Point dest = { -1,-1 }, *solutions = nullptr;
	Point pointDirChange;
	int dirToChange = 0, lgs = 0, phs = 0;
	int initDir = 0;

	void calculateRoute();
	int calculateDistance(Point Coord, char axis);
	void findMinimalDistance();
	void resetSolutions() { if (solutions != nullptr) delete solutions; lgs = phs = 0; solutions = nullptr; dest.set(-1, -1); }

public:
	NumKiller(Point _startPos, char _shape, Color _color = WHITE, TheSnakesGame* _theGame = nullptr) :Enemy(_startPos, _shape, 0, _theGame) { setColor(_color); }
	~NumKiller() {}
	virtual void move();
	void insertNewSolution(Point solCoord);
	void deleteSolution(Point solCoord);
	void updateSolutions(Point* sols, int size);
	Point getDest() { return dest; }
	int getDirToChange() { return dirToChange; }
};


#endif // !__NUM_KILLER_H