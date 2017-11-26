#ifndef __BULLET_H
#define __BULLET_H

#include "Enemy.h"

struct Bullet : Enemy {

	char shooterShape = ' ';

public:
	Bullet(const Point& snakesHead, int _dir = 0, char _shooterShape = ' ', TheSnakesGame* _theGame = nullptr) :Enemy(snakesHead, '*', _dir, _theGame) { setColor(LIGHTCYAN); shooterShape = _shooterShape; }
	~Bullet() {}

	char getShooterShape() { return shooterShape; }
	virtual void move();
//	virtual void collide() { collisionStat = true; }
//	virtual bool collided() { return collisionStat; }
};

#endif // !__BULLET_H


