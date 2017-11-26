#include <windows.h>
#include <iostream>
#include "TheSnakesGame.h"
#include "_board.h"
using namespace std;

int main() {
	TheSnakesGame game;
	bool continueGameFlag = true;


	continueGameFlag=game.setBoard(board_example);
	if (continueGameFlag)
	{
		game.init();
		game.loadMissions();
		game.run();
		
	}
	else
		gotoxy(27, 11);
	
}