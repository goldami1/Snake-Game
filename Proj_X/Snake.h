#ifndef _SNAKE_H_
#define _SNAKE_H_

#define		PLAYER_1				0
#define		PLAYER_2				1
#define	NUMPRINTCYCLE	5
#define	MAXNUMBULLETS	5
#include <cstring>
#include "Point.h"
#include "Bullet.h"
#include "Recorder.h"

class TheSnakesGame;

class Snake {

	enum { SIZE = 3 };
	int size = SIZE;
	int shot_index = 0;
	Enemy* Bullets[MAXNUMBULLETS];
	Point *body = new Point[size];						
	int direction = 4;
	Point startPos = { 4,4 };
	int startDir = UP;
	char shape, score = 0;
	char arrowKeys[4];
	Color color, headColor;
	TheSnakesGame* theGame;
	int shots = 5;
	int deactivationTimer = 0;
	bool dead = false;
	Recorder* _rec = nullptr;
	bool replay_mode = false;



public:
	void setGame(TheSnakesGame* _theGame)	{theGame = _theGame;}
	Point* getSnakeLoc()const;
	int getLength()const	{return size;}
	int getSnakeCurrentDir()const	{return direction;}
	void setPosition(int y, int x);
	void setArrowKeys(const char* keys) {
		arrowKeys[0] = keys[0];
		arrowKeys[1] = keys[1];
		arrowKeys[2] = keys[2];
		arrowKeys[3] = keys[3];
	}
	void setColor(Color c)	{color = c;}
	void setHeadColor(Color c) { headColor = c; }
	void setShape(char _shape)	{shape = _shape;}
	char getShape()	{return shape;}
	void move();											// CHANGED => COPY THIS 
	int getDirection(char key);
	void setDirection(int dir)	{direction = dir;}
	Point *getSnakeHead();
	Point getTail();
	Point getNextHeadPos();
	Snake();
	~Snake();
	void enlargeBody(const Point& newHead, const Point& oldTail);
	void shrinkBody();
	char getScore() { return score; }
	void reset();
	void resetShots() { shots = MAXNUMBULLETS; }
	void shoot();
	void deactivate();
	bool hitByBullet(Point bulletPos);
	bool activated() {return deactivationTimer == 0;}
	void reActivate();
	int getShots() { return shots; }
	void printShotStats();
	void freeSnake();
	void die() { dead = true; }
	void live() { dead = false; }
	void newScreen();
	void increaseScore() { score++; }
	void decreaseScore() { score--; }
	void increaseShots() { shots++; }
	void destroyBullets();
	int killBullet(Point bulletPos);		// new
	bool isDead() { return dead; }
	void setStartPos(Point _startPos) { if (startPos == Point(4, 4)) startPos = _startPos; }
	void resetPosition();
	void setStartDir(int _startDir) { startDir = _startDir; }
	void resetDirection() { setDirection(startDir); }
	void setRec(Recorder* Rec) {_rec = Rec;}
	void setReplayMode(bool flag) { replay_mode = flag; }

};

#endif