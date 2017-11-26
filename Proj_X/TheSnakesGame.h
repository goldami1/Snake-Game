#ifndef _THESNAKESGAME_H_
#define _THESNAKESGAME_H_

#include <fstream>
#include "io_utils.h"
#include "Snake.h"
#include "Number.h"
#include "Mission.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Flyer.h"
#include "NumKiller.h"
#include "Recorder.h"

#define		EMPTY					' '
#define		PLAYER1ARROWS			"wsad"
#define		PLAYER2ARROWS			"ikjl"
#define		PLAYER_1				0
#define		PLAYER_2				1
#define		SNAKE					'/'
#define		HEADUP					'u'
#define		HEADDOWN				'd'
#define		HEADRIGHT				'r'
#define		HEADLEFT				'l'
#define		BULLET					'*'
#define		ROW_FLYER				'!'
#define		COLUMN_FLYER			'$'
#define		NUMKILLER				'%'
#define		NO_ACTION				-18
#define		NUMPRINTCYCLE			5
#define		MAXNUMSONSCREEN			60
#define		MAXNUMOFMISSIONS		50
#define		GAME_BUTTOM_MARGINE		23
#define		GAME_LEFT_MARGINE		0
#define		GAME_RIGHT_MARGINE		79
#define		GAME_TOP_MARGINE		4
#define		WINNINGSCORE			12
#define		BLANK					-1
#define		PLUS					-2
#define		MINUS					-3
#define		MULT					-4
#define		DIV						-5
#define		COLLISION_SNAKE			1
#define		COLLISION_NUM			2
#define		COLLISION_BULLET		3
#define		COLLISION_RICOCHET		4
#define		COLLISION_ENEMY			5
#define		COLLISION_ENEMY_BPROOF  6
#define	    COLLISION_NUM_KILLER	7
#define		BULLET_RICOCHET			'O'
#define     COLLIDION_HORIZ_FLYER   8
#define		VERTICAL				10
#define		HORIZONTAL				11
#define		UP						1
#define		DOWN					-1
#define		LEFT					2
#define		RIGHT					-2
#define		STOP					0
#define		NUMOFENEMIES			5
#define		MAXCHARSONSTRING		120








enum { ROWS = 24, COLS = 80 };
enum SubMenu { Exit = '1', GoToMM, Resume, RestartM, NewM, RestartG, Replay };
enum MainMenu { ShowInstructions = '1', BeginGame, EXIT = '9' };

class TheSnakesGame {
	enum {ESC = 27};
	Snake s[2];
	Number nums[MAXNUMSONSCREEN];
	Mission missions[MAXNUMOFMISSIONS];
	int currentMissionID = NULL;
	int numsOnScreen = 0;
	bool replayMode = false;
	Recorder rec;
	int time_g = 0;
	
	char originalBoard[ROWS][COLS + 1];	// this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e. changes on board are done here
	void handleObjectCreationFromBoard(int row, int col); // '@' , '#' are the start points of the Snakes
	void deleteNumFromArray(Number *num);
	void playerWonSeq(bool s1won, bool s2won);
	void remove_X_NumsOfBoard(int X);
	int MainMenu(bool isFirstRun);
	int SubMenu();
	Enemy** Enemies = nullptr;
	int startNumsRec = 0, endNumsRec = 0;
	int maxNumOfMissions = 2;
	bool missionEnd = false;


	void printVirtaulBoard();
	Number* findNumInBoard(const Point& headNext);
	void printInstructions();
	void printMenuFrame();
	void printMessageFrame();
	void handleSubMenu(bool &run_flag);
	void printWinningMessage(int player_ref);
	void clearBoard();
	void markPossibleSolutions();
	void mark_numbers(Color color);
	void printPlayerStats();
	void setNewMission();


public:
	bool isValidNumPos(int NumXCoord, int NumYCoord, int len); 
	bool setBoard(const char* boardToCopy[ROWS]); //copy board sent to us into originalBoard, setArrowKeys, setColor
	void init(); //copy original board to actual board and set Snakes Start point
	int colided(const Point& p);
	int colided(const Point& p, const Enemy* enemyObject);			// new
	void run(); // run 2 Snakes with Keyboard
	void updateLocationInBoard(const Snake *s, const Point& head, const Point& tail);
	void updateLocationInBoard(const Number *n, const Point& MSB, const int length);
	void updateLocationInBoard(const Enemy* enemy, const Point& loc, Point& oldLoc);
	void updateLocationInBoard(Point p, char c);
	bool checkMissionSuccess(Snake& s, const Point& headNext, const Point& oldTail);
	Snake* snakeCollide(const Point& p);
	int numCollide(const Point& p);
	Snake* getSecondSnake(const Snake *snake1);
	Point* getDetValidPosInBoard();
	Point* getValidPosInBoard();
	void setEnemies();
	void resetEnemies();
	void moveEnemies();
	void removedeadEnemies();
	void updateNumKiller();
	void setBoardForReplay();
	void loadPreviousPlayerStats(bool _s1won, bool _s2won);
	void NewMissionNotice(bool _runflag);

	void loadMissions();

	
	
};

#endif