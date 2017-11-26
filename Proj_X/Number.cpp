#include "Number.h"
#include "TheSnakesGame.h"

void Number::getValidXYCoord(int *xCoord, int *yCoord)
{
	int NumYCoord, NumXCoord;
	bool found = false;

	while (!found)
	{
		NumYCoord = rand() % ROWS;
		NumXCoord = rand() % COLS;
		if (theGame->isValidNumPos(NumXCoord, NumYCoord, len))
			found = true;
	}

	*xCoord = NumXCoord;
	*yCoord = NumYCoord;
}

int Number::getNumLen(int num)
{
	int numOfDigits = 0;
	if (num == 0)
		return 1;
	while (num > 0)
	{
		numOfDigits++;
		num /= 10;
	}

	return numOfDigits;
}

int Number::getNumsRange()
{
	return rand() % 3 + 1;
}

void Number::printNumber()
{
	
	gotoxy(this->body[0].getX(), this->body[0].getY());
	cout << this->val;
	theGame->updateLocationInBoard(this, this->body[0], this->len);
}

void Number::setNumber()
{
	int rangeOfNumber = getNumsRange();
	if (rangeOfNumber == 1)
		val = rand() % 26;
	else if (rangeOfNumber == 2)
		val = rand() % 56 + 26;
	else
		val = rand() % 88 + 82;
	len = getNumLen(val);

	body = new Point[len];
}

void Number::setnumberPart2()
{
	int NumXCoord, NumYCoord;
	if (val == 0 && body[0].getY() == 0 && body[0].getX() == 0)
		val = val + 0;
	getValidXYCoord(&NumXCoord, &NumYCoord);
	for (int i = 0;i < len;i++)
		body[i].set(NumXCoord + i, NumYCoord);
}

void Number::deleteNumber()
{
//	if (body != nullptr)
	//	delete[]body;
//	body = nullptr;
//	len = val = -1;
}

Point* Number::getNumberLoc()	/*	don't forget to delete the returned value after each use of this function*/
{
	int i;
	Point* numDup = new Point[len];

	for (i = 0; i < len; i++)
		numDup[i] = body[i];

	return numDup;
}

bool Number::doesIncludeThePoint(const Point& p)
{
	for (int j = 0; j < len; j++)
		if (body[j].getX() == p.getX() && body[j].getY() == p.getY())
			return true;
	return false;
}



void Number::set(Number src)
{
	Point* newBody = src.getNumberLoc();

	body = newBody;
	val = src.getNumVal();
	len = getNumLen(val);
	theGame = src.theGame;
}


Number::Number()
{

}
/*/
Number::Number(const Number &toCopy)
{
	val = toCopy.getNumVal();
	len = toCopy.len;
	//if (body != nullptr) delete body;
	body = new Point[len];
	setGame(toCopy.theGame);
	for(int i=0;i<len;i++)
		body[i] = toCopy.body[i];
}
*/