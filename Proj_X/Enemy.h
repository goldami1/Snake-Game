#ifndef __ENEMY_H
#define __ENEMY_H

#include "Point.h"
class TheSnakesGame;

#define		UP						1
#define		DOWN					-1
#define		LEFT					2
#define		RIGHT					-2
#define		STOP					0
#define		NOT_IN_USE				-15
#define		ROW_FLYER				'!'
#define		DEVOURER				'%'
#define		GAME_BUTTOM_MARGINE		23
#define		GAME_LEFT_MARGINE		0
#define		GAME_RIGHT_MARGINE		79
#define		GAME_TOP_MARGINE		4


class Enemy {

private:
	char shape;
	int dir;
	Point loc;
	char snake_shape =' ';
	TheSnakesGame* theGame;
	int collisionStat = 0;
	Color _color = WHITE;
	bool bulletProof = false;
	bool dead = false;
public:
	Enemy(const Point& newLoc, char _shape = '*', int _dir = 0, TheSnakesGame* _theGame = nullptr) :shape(_shape), dir(_dir) {
		loc.set(newLoc.getX(), newLoc.getY()), setGame(_theGame);
		if (shape == ROW_FLYER) bulletProof = true;
		dead = false;
	}
	~Enemy() { }
	virtual void move();
	bool colided() {}
	char getShape()const { return shape; }
	void setGame(TheSnakesGame* _theGame) { theGame = _theGame; }
	char getSnakeShape() { return snake_shape; }
	Point getNextPos() { return loc.next(dir); }
	int getCollisionStat() { return collisionStat; }
	void setColor(Color color) { _color = color; }
	Point getLoc() { return loc; }
	void setLoc(Point _loc) {loc = _loc;}
	void die();
	int getDirection() { return dir; }
	void setDirection(int _dir) {if (_dir == UP || _dir == DOWN || _dir == LEFT || _dir == RIGHT) dir = _dir;}
	bool isDead() { return dead; };
	bool isBulletProof() { return bulletProof; }
	Color getColor() { return _color; }


};

#endif // !__ENEMY_H


