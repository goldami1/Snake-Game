#ifndef __FLYER_H
#define __FLYER_H
#include "Enemy.h"

#define		VERTICAL				10
#define		HORIZONTAL				11
#define		UP						1
#define		DOWN					-1
#define		LEFT					2
#define		RIGHT					-2
#define		GAME_BUTTOM_MARGINE		23
#define		GAME_LEFT_MARGINE		0
#define		GAME_RIGHT_MARGINE		79
#define		GAME_TOP_MARGINE		4

struct Flyer : Enemy {
private:
	bool isBouncer = false;
	int type = HORIZONTAL;
	Color color = WHITE;
	Point startPos = { 4, 4 };

public:
	Flyer(Point _startPos, char _shape, int _dir = 0, bool _isBouncer = false, Color _color=WHITE, int _type=HORIZONTAL, TheSnakesGame* _theGame = nullptr) :Enemy(_startPos, _shape, _dir, _theGame) 
	{
		setColor(_color); isBouncer = _isBouncer; color = _color;
		if (_type== HORIZONTAL || _type == VERTICAL) type = _type;
		else type = HORIZONTAL;
		startPos = _startPos;
	}
	~Flyer() {}

	virtual void move();
	bool IsBouncer() { return isBouncer; }
	void resetPos() { Enemy::setLoc(startPos); }
	void checkForBoundary();
	void bounce() { if (!isBouncer) return; Enemy::setDirection(Enemy::getDirection()*(-1)); }


};



#endif 