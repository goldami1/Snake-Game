#include "Snake.h"
#include "TheSnakesGame.h"

void Snake::setPosition(int y, int x)
{
	for (int i = 0;i < size;i++)
		this->body[i].set(x, y);
}

Snake::Snake()
{
	for (int j = 0; j < MAXNUMBULLETS; j++)
		Bullets[j] = nullptr;
}

Snake::~Snake()
{
	delete[]body;
}

Point* Snake::getSnakeLoc()const	//	don't forget to delete the returned value after each use of this function
{
	int i;
	Point* snakeDup = new Point[size];
	
	for (i = 0;i < size;i++)
		snakeDup[i] = body[i];

	return snakeDup;
}

void Snake::move()
{
		for (int i=0; i<MAXNUMBULLETS; i++)
			if (Bullets[i] != nullptr)
				Bullets[i]->move();

		for (int i = 0; i < MAXNUMBULLETS; i++)
		{
			if (Bullets[i] != nullptr)
			{
				if (Bullets[i]->getCollisionStat() == COLLISION_SNAKE)
				{
					if (Bullets[i]->getSnakeShape() != this->getShape())
					{
						shots++;
						printShotStats();
					}
					delete Bullets[i];
					Bullets[i] = nullptr;
				}
				else if (Bullets[i]->isDead())
				{
					delete Bullets[i];
					Bullets[i] = nullptr;

				}
			}
		}
		
		if (deactivationTimer > 0)
		{
			deactivationTimer--;
			if (deactivationTimer == 0)
				reActivate();
			return;
		}

		int collisionStatus = theGame->colided(body[0].next(direction));
		if (!(collisionStatus == 1) && direction != STOP)
		{
			Point tail = body[size - 1];

			body[size - 1].draw(' ');
			for (int i = size - 1; direction != STOP && i > 0; --i)
				body[i] = body[i - 1];

			if (collisionStatus == COLLISION_SNAKE)
				direction = STOP;

			if (collisionStatus == COLLISION_NUM)
			{
				if (theGame->checkMissionSuccess(*this, body[0].next(direction), tail))
					increaseScore();
				else
					theGame->getSecondSnake(this)->increaseScore();
			}

		body[0].move(direction);
		setTextColor(headColor);
		body[0].draw(this->getShape());

		setTextColor(color);
		body[1].draw(this->getShape());
		setTextColor(Color::WHITE);
		theGame->updateLocationInBoard(this, body[0] ,tail);
	}
}

Point * Snake:: getSnakeHead()	//	don't forget to delete the returned value after each use of this function
{
	Point *res = new Point;
	res->set(this->body[0].getX(), this->body[0].getY());
	return res;
}

Point Snake::getTail()
{
	Point res;
	int len = this->getLength();

	res.set(this->body[len-1].getX(), this->body[len-1].getY());
	return res;
}

int Snake::getDirection(char key)
{
	int currDir = this->getSnakeCurrentDir();

	for (int i = 0; i < 4; ++i) {
		if (key == arrowKeys[i] ) 
		{
			int _dir=NO_ACTION;
			if (i == 0) _dir = UP; 
			if (i == 1) _dir = DOWN;
			if (i == 2) _dir = LEFT;
			if (i == 3) _dir = RIGHT;
			if (currDir != _dir*(-1))
				return _dir;
		}
	}
	return NO_ACTION;
}

void Snake::enlargeBody(const Point& newHead, const Point& oldTail)
{
	size++;
	body = (Point*)realloc(body, size*sizeof(Point));
	body[size-1] = oldTail;
}

Point Snake::getNextHeadPos()
{
	return body[0].next(this->getSnakeCurrentDir());
}

void Snake::reset()
{
	shots = 5;
	size = SIZE;
	direction = 4;
	score = 0;
	body = (Point*)realloc(body, SIZE * sizeof(Point));
	deactivationTimer = 0;

	for (int i = 0; i < MAXNUMBULLETS; i++)
		if (Bullets[i] != nullptr) { delete Bullets[i]; Bullets[i] = nullptr; }
}

void Snake::shoot()
{
	int j;
	for (j = 0; j < MAXNUMBULLETS; j++)
		if (Bullets[j] == nullptr) break;

	if (shots > 0 && j< MAXNUMBULLETS)
	{

		shot_index = j;
		if (theGame->colided(getNextHeadPos()) != COLLISION_BULLET)
			Bullets[shot_index] = new Bullet(getNextHeadPos(), direction, shape, theGame);
		shots--;

		printShotStats();
	}
	
}

bool Snake::hitByBullet(Point bulletPos)
{
	for (int i = 0; i < size; i++)
		if (body[i] == bulletPos)
			return true;
	return false;

}

void Snake::reActivate()
{
	int player;

	if (shape == '@') player = PLAYER_1;
	else player = PLAYER_2;

	if (!replay_mode)
	{
		Point* validPos = theGame->getValidPosInBoard();
		body[0].set(validPos->getX(), validPos->getY());

		_rec->insertPts(*validPos, player);
		delete validPos;
	}
	else
	{
		Point recordedLoc = _rec->getNextPts(player);
		body[0].set(recordedLoc.getX(), recordedLoc.getY());

	}
	

	
}

void Snake::deactivate()
{
	if (deactivationTimer > 0) return;
	if (!dead) PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME);
	else  PlaySound(TEXT("snakeLose.wav"), NULL, SND_FILENAME);

	for (int i = 0; i < size; i++)
	{
		theGame->updateLocationInBoard(body[i], EMPTY);
		setTextColor(LIGHTMAGENTA);
		body[i].draw(shape);
		Sleep(50);
		body[i].draw(' ');
		Sleep(50);
	}
	 this->deactivationTimer = NUMPRINTCYCLE * 5; 
}

void Snake::printShotStats()
{
	int x;
	Color c;
	if (this->shape == '@') { c = LIGHTGREENONMAGENTA; x = 67; }
	else { c = YELLOWONMAGENTA; x = 71; }

	gotoxy(x, 2);
	setTextColor(c);
	cout << this->shots;
	setTextColor(WHITE);
}

void Snake::freeSnake()
{
	for (int i = 0; i < MAXNUMBULLETS; i++)
		if (Bullets[i] != nullptr) { delete Bullets[i]; Bullets[i] = nullptr; }

}

void Snake::newScreen()
{
	resetPosition();
	resetDirection();
	live();
	resetShots();
	destroyBullets();
	deactivationTimer = 0;

}

void Snake::destroyBullets()
{
	for (int i = 0; i < MAXNUMBULLETS; i++)
	{
		if (Bullets[i] != nullptr)
		{
			setTextColor(WHITE);
			gotoxy(Bullets[i]->getLoc().getX(), Bullets[i]->getLoc().getY());
			cout << EMPTY;
			theGame->updateLocationInBoard(Bullets[i]->getLoc(), EMPTY);
			delete Bullets[i];
			Bullets[i] = nullptr;
		}
	}
}

int Snake:: killBullet(Point bulletPos)
{
	for (int i = 0; i < MAXNUMBULLETS; i++)
	{
		if (Bullets[i] != nullptr)
			if (Bullets[i]->getLoc() == bulletPos)
			{
				Bullets[i]->die();
				return 1;
			}
	}

	return 0;
}

void Snake::resetPosition()
{

	for (int i = 0; i < size; i++)
	{
		theGame->updateLocationInBoard(body[i], EMPTY);
		if (deactivationTimer == 0)
		{
			setTextColor(LIGHTMAGENTA);
			body[i].draw(shape);
			Sleep(50);
			setTextColor(WHITE);
			body[i].draw(EMPTY);
			Sleep(50);
		}
		else {setTextColor(WHITE); body[i].draw(EMPTY);}
		
	}

	setPosition(startPos.getX(), startPos.getY());
}

void Snake::shrinkBody()
{
	body = (Point*)realloc(body, sizeof(Point)*(this->getLength() - 1));
	size--;
}