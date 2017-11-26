#include "Recorder.h"

void Recorder::recordInitNums(int _size, Number nums[])
{
	int j=0;

	for (int i = 0; i < _size; i++)
	{
		if (nums[i].getNumVal() != -1)
		{
			numbersArr[j].set(nums[i]);
			j++;
		}
	}

	startOfNums = endOfNums = j;
}

void Recorder::insertNum(Number num)
{
	if (num.getNumVal() != -1)
	{
		numbersArr[endOfNums].set(num);
		endOfNums++;
	}
	
}

void Recorder::getNumsArr(Number nums[], int &start, int& end)
{
	int j = 0;

	for (int i = 0; i < endOfNums; i++)
	{
		if (numbersArr[i].getNumVal() != -1)
		{
			nums[j].set(numbersArr[i]);
			j++;
		}

	}

	endOfNums = j;
	start = startOfNums;
	end = endOfNums;

}


void Recorder::insertAction(int currTime, char act)
{
	if(actionsArr==nullptr)
	{
		size[PHS_ACT] = 1;
		size[LGS_ACT] = 0;
		actionsArr = new action[size[PHS_ACT]];
	}
	else if(size[LGS_ACT]==size[PHS_ACT])
	{
		size[PHS_ACT] *= 2;
		actionsArr = (action*)realloc(actionsArr, sizeof(action)*size[PHS_ACT]);
	}
	
	actionsArr[size[LGS_ACT]].act = act;
	actionsArr[size[LGS_ACT]].currTime = currTime;

	size[LGS_ACT]++;
}





void Recorder::insertPts(Point p, int player)
{
	if (pointsArr[player] == nullptr)
	{
		size[player * 2 + 4] = 1;
		size[player * 2 + 5] = 0;
		pointsArr[player] = new Point[size[player * 2 + 4]];
	}
	else if (size[player * 2 + 4] == size[player * 2 + 5])
	{
		size[player * 2 + 4] *= 2;
		pointsArr[player] = (Point*)realloc(pointsArr[player], sizeof(Point)*size[player * 2 + 4]);
	}

	pointsArr[player][size[player*2+5]] = p;
	size[player * 2 + 5]++;
}

Point Recorder::getNextPts(int player)
{
	if (pointsArr[player] != nullptr && index_pts[player] < size[player*2+5])
		return pointsArr[player][index_pts[player]++];
	else
		return Point(-1, -1);
}



char Recorder::getAction(int currTime)
{
	if (index_act < size[LGS_ACT] && currTime == actionsArr[index_act].currTime)
	{
		char key = actionsArr[index_act++].act;
		return key;

	}
		
	return '\0';	
}



void Recorder::resetIndices()
{
	for (int i = 0; i < 2; i++)
		index_pts[i] = 0;
	
	index_act = 0;
}

void Recorder::deleteRecords()
{

    for (int i = 0; i < 2; i++)
	{
		if (pointsArr[i] != nullptr) delete pointsArr[i];
		pointsArr[i] = nullptr;
		index_pts[i] = 0;
	}

	if (actionsArr != nullptr)
		delete actionsArr;

	actionsArr = nullptr;

	index_act = 0;

	for (int i = 0; i < 6; i++)
		size[i] = 0;

}

void Recorder:: printActionsArr()
{
	setTextColor(BLACKONGREY);
	gotoxy(3, 60);
	if (actionsArr == nullptr) return;

	for (int i = 0; i < size[LGS_ACT]; i++)
		cout << actionsArr[i].act << ", ";

}