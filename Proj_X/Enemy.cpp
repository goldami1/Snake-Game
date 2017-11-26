#include "Enemy.h"
#include "TheSnakesGame.h"

void Enemy::move()
{
		if (dead) return;

		Snake* TheSnake;
		Point initDummy, Dummy;

		initDummy.set(this->getLoc().getX(), this->getLoc().getY());
		Dummy = initDummy;

		loc.draw(EMPTY);

		collisionStat = theGame->numCollide(Dummy.next(dir));							// look for NUMBER collisions
		Dummy = initDummy;
		TheSnake = theGame->snakeCollide(Dummy.next(dir));								// look for SNAKE collisions		// next pos
		Dummy = initDummy;

		if (collisionStat == COLLISION_NUM && shape == BULLET)
		{
			die();
			return;
		}

		if (TheSnake == nullptr) TheSnake = theGame->snakeCollide(this->loc);												// curr pos
	
		if (TheSnake != nullptr)														// SNAKE collision
		{
			collisionStat = COLLISION_SNAKE;
			snake_shape = TheSnake->getShape();
			if (shape == NUMKILLER) TheSnake->die();
			TheSnake->deactivate();
			if (shape == BULLET)
			{
				die();
				return;
			}
			
		}

		collisionStat = theGame->colided(Dummy.next(dir), this);			// Check for Bullet/Creature collision in next pos
		if (collisionStat == 0 && shape == BULLET || shape == ROW_FLYER)
			collisionStat = theGame->colided(Dummy.next(dir), this);			// If double speed mover check for collisions in next next pos

		if (collisionStat != 0)															// Collision detected
		{
			if (shape == BULLET) die();
			else if (collisionStat == COLLISION_BULLET)
				if (!bulletProof) die();
		}

		if (dead) return;																// Abort move if dead

		if (shape == NUMKILLER)															// Abort move if NUMKILLER and there is no destination
			if (((NumKiller*)this)->getDest() == Point(-1, -1))
			{
				theGame->updateLocationInBoard(getLoc(), shape);
				setTextColor(LIGHTMAGENTA);
				loc.draw(shape); 
				collisionStat = theGame->colided(this->getLoc(), this);
				if (collisionStat == COLLISION_BULLET)
					die();

				return;
			}

		setTextColor(WHITE);
		loc.draw(EMPTY);
		theGame->updateLocationInBoard(this, this->getNextPos(), loc);					// Not dead => update new location in virtual and actual borad
		loc.move(dir);
		setTextColor(_color);
		loc.draw(this->getShape());
}


void Enemy::die()
{
	if (shape != BULLET) PlaySound(TEXT("EnemyDie.wav"), NULL, SND_FILENAME);
	dead = true;
	setTextColor(LIGHTMAGENTA);
	loc.draw(shape);
	Sleep(50);
	setTextColor(WHITE);
	loc.draw(EMPTY);
	theGame->updateLocationInBoard(loc, EMPTY);

}