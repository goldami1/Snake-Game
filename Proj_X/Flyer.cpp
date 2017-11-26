#include "Flyer.h"

void Flyer::move()
{
	if (isBouncer) checkForBoundary();
	Enemy::move();
	if (isBouncer) checkForBoundary();
	if (type == HORIZONTAL)
		Enemy::move();
	if (isBouncer) checkForBoundary();
}

void Flyer::checkForBoundary()
{
	Point loc;
	loc.set(this->getLoc().getX(), this->getLoc().getY());
	loc.next(getDirection());

	if (this->type == HORIZONTAL)
		if (loc.getY() == GAME_LEFT_MARGINE || loc.getX() == GAME_RIGHT_MARGINE)
			this->bounce();

	if (this->type == VERTICAL)
		if (loc.getY() == GAME_TOP_MARGINE ||( loc.getY() == GAME_BUTTOM_MARGINE && getDirection() == DOWN))
			this->bounce();
	
	

}