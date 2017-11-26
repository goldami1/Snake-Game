#ifndef __RECORDER_H
#define __RECORDER_H

#include "Number.h"

#define		PHS_NUM		0
#define		PHS_ACT		1
#define		LGS_NUM		2	
#define		LGS_ACT		3
#define		PHS_PTS1	4
#define		LGS_PTS1	5
#define		PHS_PTS2	6
#define		LGS_PTS2	7
#define		MAXNUMSONSCREEN			60
#define		PLAYER_1				0
#define		PLAYER_2				1

class Recorder
{
private:
	typedef struct _action{
		int currTime;
		char act;
	}action;

	action *actionsArr = nullptr;
	Number numbersArr[MAXNUMSONSCREEN];
	Point *pointsArr[2];
	int size[6];
	int index_act, index_num, sizeOfInitNums, index_pts[2];

	int endOfNums = 0, startOfNums = 0;

public:
	Recorder() :actionsArr(nullptr), index_act(0), index_num(0), sizeOfInitNums(0), index_pts{0,0} {}
	~Recorder() { }
	
//	void getInitNums(int &_size, Number nums[]);

	void insertAction(int currTime, char act);
	void insertPts(Point p, int player);
	Point getNextPts(int player);

	char getAction(int currTime);
	bool endOfNumsArr() { return index_num >= size[LGS_NUM]; }
	void resetIndices();

	void recordInitNums(int _size, Number nums[]);
	void insertNum(Number num);
	void getNumsArr(Number nums[], int &start, int& end);
	void deleteRecords();
	//	bool endOfNumsArr() { return index_num >= size[LGS_NUM]; }
	void printActionsArr();

};

#endif // !__RECORDER_H