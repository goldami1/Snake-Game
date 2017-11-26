#include "NumKiller.h"

void NumKiller::move()
{
	Point currLoc = getLoc();
	gotoxy(currLoc.getX(), currLoc.getY());
	setTextColor(LIGHTMAGENTA);
	cout << getShape();
	setTextColor(Color::WHITE);
	int distanceBefore = calculateDistance(dest, 'x') + calculateDistance(dest, 'y');
	Point destBefore = dest, destAfter;

	if (getColor() == LIGHTMAGENTA) setColor(LIGHTRED); else setColor(LIGHTMAGENTA);

	for (int i = 0; i < 2; i++)
	{
		if (!(dest == Point(-1, -1)))
		{

			Point check;
			int dirSign;

			if (initDir < 0) dirSign = 1;
			if (initDir > 0) dirSign = -1;

			check.set(currLoc.getX() + i*dirSign, currLoc.getY());
			if (check == pointDirChange && dirToChange != NOT_IN_USE)
				setDirection(dirToChange);
		}
		else setDirection(STOP);

		Enemy::move();

	}

	setTextColor(Color::WHITE);

	destAfter = dest;
	int distanceAfter = calculateDistance(dest, 'x') + calculateDistance(dest, 'y');

	if (distanceAfter > distanceBefore && destAfter == destBefore)
		calculateRoute();
}

void NumKiller::insertNewSolution(Point solCoord)
{
	if(solutions==nullptr)
	{
		lgs = 0;
		phs = 1;
		solutions = new Point[phs];
		dest = solCoord;
		calculateRoute();
		setDirection(initDir);
		pointDirChange.set(dest.getX(), getLoc().getY());
		
	}
	else
	{
		if (lgs == phs)
		{
			phs *= 2;
			solutions = (Point*)realloc(solutions, sizeof(Point)*phs);
		}

		int currDist, coordDist;

		currDist = calculateDistance(dest, 'x') + calculateDistance(dest, 'y');
		coordDist = calculateDistance(solCoord, 'x') + calculateDistance(solCoord, 'y');

		if (coordDist < currDist)
		{
			dest = solCoord;
			pointDirChange.set(dest.getX(), getLoc().getY());
			calculateRoute();
			setDirection(initDir);
		
		}
	}
	
	solutions[lgs] = solCoord;
	lgs++;
}

void NumKiller::deleteSolution(Point solCoord)
{
	bool isFound = false;

	if (solutions == nullptr)
		return;

	for(int i=0;i<lgs;i++)
	{
		if (!(solutions[i] == Point(-1, -1)))
		{
			if (solutions[i] == solCoord)
				solutions[i].set(-1, -1);

			else if (!isFound) isFound = true;
		}
			
	}

	if(!isFound)
	{
		lgs = phs = 0;
		delete solutions;
		solutions = nullptr;
		dest.set(-1,-1);
		setDirection(STOP);
		return;
	}

	if (solCoord == dest)
	{
		dest = Point(-1, -1);
		setDirection(STOP);
		findMinimalDistance();
	}
		

}

int NumKiller::calculateDistance(Point Coord, char axis)
{

	int D_inBoard, D_throughWall;
	int currlocX, currlocY, CoordX, CoordY;

	currlocX = getLoc().getX();
	currlocY = getLoc().getY();
	CoordX = Coord.getX();
	CoordY = Coord.getY();

	if(axis=='x')
	{
		D_inBoard = currlocX - CoordX;
		if (D_inBoard >= 0)
			D_throughWall = GAME_RIGHT_MARGINE - CoordX + 1 + currlocX;							// MOVE TOWARDS RIGHT WALL	
		else
		{
			D_throughWall = currlocX - GAME_LEFT_MARGINE + GAME_RIGHT_MARGINE - CoordX + 1;		// MOVE TOWARDS LEFT WALL
			D_inBoard *= -1;
		}
		
	}
	
	if(axis=='y')
	{
		D_inBoard = currlocY - CoordY;
		if (D_inBoard >= 0)
			D_throughWall = GAME_BUTTOM_MARGINE - currlocY + CoordY - GAME_TOP_MARGINE;		// MOVE TOWARDS THE BOTTOM WALL
		else
		{
			D_throughWall = currlocY - GAME_TOP_MARGINE + GAME_BUTTOM_MARGINE - CoordY;		// MOVE TOWARDS THE TOP WALL
			D_inBoard *= -1;
		}
			
	}

	return min(D_inBoard, D_throughWall);
}

void NumKiller::findMinimalDistance()
{
	bool found = false;
	int currMin = 100;
	int xDist, yDist;
	Point minPoint(-1, -1);

	initDir = STOP;
	dirToChange = NOT_IN_USE;

	if (solutions == nullptr)
		return;
	for(int i=0;i<lgs;i++)
	{
		if (!(solutions[i] == Point(-1, -1)))
		{
			if (!found) found = true;
			xDist = calculateDistance(solutions[i], 'x');
			yDist = calculateDistance(solutions[i], 'y');
			if (xDist + yDist < currMin)
			{
				currMin = xDist + yDist;
				minPoint = solutions[i];
			}
		}
	}

	if (found)
	{
		dest = minPoint;
		pointDirChange.set(dest.getX(), getLoc().getY());
		calculateRoute();
		setDirection(initDir);
	}
	else
	{
		lgs = phs = 0;
		dest.set(-1, -1);
		delete solutions;
		solutions = nullptr;
	}
	
}


void NumKiller::calculateRoute()
{
	int D_inBoard, D_throughWall;
	int currlocX, currlocY, CoordX, CoordY;
	bool sameXaxis = false, sameYaxis = false;

	currlocX = getLoc().getX();
	currlocY = getLoc().getY();
	CoordX = dest.getX();
	CoordY = dest.getY();

		D_inBoard = currlocX - CoordX;
		if (D_inBoard > 0)
		{
			D_throughWall = GAME_RIGHT_MARGINE - CoordX + 1 + currlocX;							// MOVE TOWARDS RIGHT WALL
			if (D_inBoard > D_throughWall) initDir = RIGHT;
			else initDir = LEFT;
		}
				
		else if (D_inBoard < 0)
		{
			D_inBoard *= -1;
			D_throughWall = currlocX - GAME_LEFT_MARGINE + GAME_RIGHT_MARGINE - CoordX + 1;		// MOVE TOWARDS LEFT WALL
			if (D_inBoard > D_throughWall) initDir = LEFT;
			else initDir = RIGHT;
		}
		else  sameYaxis = true;
		

		D_inBoard = currlocY - CoordY;
		if (D_inBoard > 0)
		{
			D_throughWall = GAME_BUTTOM_MARGINE - currlocY + CoordY - GAME_TOP_MARGINE;		// MOVE TOWARDS THE BOTTOM WALL
			if (D_inBoard > D_throughWall) { if (!sameYaxis) dirToChange = DOWN; else initDir = DOWN; }
			else
				if (!sameYaxis) dirToChange = UP; else initDir = UP;
		}
			
		else if (D_inBoard < 0)
		{
			D_inBoard *= -1;
			D_throughWall = currlocY - GAME_TOP_MARGINE + GAME_BUTTOM_MARGINE - CoordY;		// MOVE TOWARDS THE TOP WALL
			if (D_inBoard > D_throughWall) if (!sameYaxis) dirToChange = UP; else initDir = UP;
			else if (!sameYaxis) dirToChange = DOWN; else initDir = DOWN;
		}
		else sameXaxis = true;

		if (sameXaxis || sameYaxis) dirToChange = NOT_IN_USE;

			

}


void NumKiller::updateSolutions(Point* sols, int size)
{
	if (solutions != nullptr) resetSolutions();

	solutions = sols;
	lgs = phs = size;
	findMinimalDistance();
}