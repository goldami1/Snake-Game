#include "TheSnakesGame.h"
#include "Opening.h"
#include "Color.h"

int TheSnakesGame::MainMenu(bool isFirstRun)
{
	char selection;
	bool keyNOTvalid = true, check=false;
	printMenuFrame();

	gotoxy(3, 1); 
	setTextColor(Color::LIGHTGREYONBLUE);
	cout << "          WELCOME TO THE SNAKES GAME. THE BEST GAME THAT EXISTS!            ";           
	gotoxy(3, 2);
	setTextColor(Color::WHITEONBLUE);
	cout << "         (1) Show Instructions      (2) Begin Game      (9) Exit            "; 

	printOpener();

	while (!check)
	{
		while (keyNOTvalid)
		{
			selection = _getch();
			keyNOTvalid = false;
			selection == MainMenu::EXIT || selection == MainMenu::BeginGame || selection == MainMenu::ShowInstructions ? keyNOTvalid == false : keyNOTvalid = true;
		}

		PlaySound(TEXT("click.wav"), NULL, SND_FILENAME);

		check = true;
		if (selection == MainMenu::EXIT)
			return MainMenu::EXIT;
		else if (selection == MainMenu::BeginGame)
			return MainMenu::BeginGame;
		else if (selection == MainMenu::ShowInstructions)
		{
			check = false;
			keyNOTvalid = true;
			printInstructions();
		}
	}
	
	return 1;
}

int TheSnakesGame::SubMenu()
{
	char selection;
	bool keyNOTvalid = true;

	
	printMenuFrame();

	gotoxy(3, 1);
	setTextColor(Color::WHITEONBLUE);
	cout << "(1) Exit                    (2) Go to Main Menu               (3) Resume    ";
	gotoxy(3, 2);
	cout << "(4) Restart Mission    (5) New Mission    (6) Restart Game    (7) Replay    ";
	setTextColor(Color::WHITE);

	if (replayMode || !missionEnd)
	{
		gotoxy(65, 2);
		setTextColor(BLACKONBLUE);
		cout << "(7) Replay";
		setTextColor(WHITE);

	}
	
	while(keyNOTvalid)
	{
		selection = _getch();

		if (replayMode || !missionEnd)
			while (selection == SubMenu::Replay)
				selection = _getch();

		keyNOTvalid = false;
		if (selection >= SubMenu::Exit && selection <= SubMenu::Replay)
		{
			
			PlaySound(TEXT("click.wav"), NULL, SND_FILENAME);
			return selection;
		}
		
		else
			keyNOTvalid = true;
	}
	return 1;
}

bool TheSnakesGame::isValidNumPos(int NumXCoord, int NumYCoord, int len)
{

	bool top = false, bottom = false, left = false, right = false;

	if (NumYCoord < GAME_TOP_MARGINE) return false;

	if (NumXCoord + len - 1 >= COLS)												//number falls to the right of the right margine
		return false;

	if (NumXCoord == GAME_LEFT_MARGINE) left = true;
	if (NumXCoord + len == COLS) right = true;
	if (NumYCoord == GAME_TOP_MARGINE) top = true;
	if (NumYCoord == ROWS - 1) bottom = true;

	if (!left)																									// check left side
	{
		if (board[NumYCoord][NumXCoord - 1] == HEADRIGHT)
			return false;

		if (board[NumYCoord][NumXCoord - 1] - '0' >= 0 && board[NumYCoord][NumXCoord - 1] - '0' <= 9)
			return false;
	}

	if (!right)																									// check right side
	{
		if (board[NumYCoord][NumXCoord + len] == HEADLEFT)
			return false;

		if (board[NumYCoord][NumXCoord + len] - '0' >= 0 && board[NumYCoord][NumXCoord + len] - '0' <= 9)
			return false;
	}

	if (!top)																									// check top
	{

		for (int i = 0;i < len && NumXCoord + i < COLS; i++)
		{
			if (i >= len) break;

			if (board[NumYCoord - 1][NumXCoord + i] == HEADDOWN)
				return false;

			if (board[NumYCoord - 1][NumXCoord + i] - '0' >= 0 && board[NumYCoord - 1][NumXCoord + i] - '0' <= 9)
				return false;
		}
	}

	if (!bottom)																								// check bottom
	{
		for (int i = 0;i < len && NumXCoord + i < COLS; i++)
		{
			if (i >= len) break;

			if (board[NumYCoord + 1][NumXCoord + i] == HEADUP)
				return false;
			if (board[NumYCoord + 1][NumXCoord + i] - '0' >= 0 && board[NumYCoord + 1][NumXCoord + i] - '0' <= 9)
				return false;
		}
	}

	for (int i = 0;i < len;i++)
		if (board[NumYCoord][NumXCoord + i] != EMPTY)														// switched + i to x coord
			return false;

	return true;
}

void TheSnakesGame::handleObjectCreationFromBoard(int row, int col)
{
	Point _startPos;

	if (originalBoard[row][col] == '@')
	{
		s[0].setPosition(row, col);
		_startPos.set(row, col);
		s[0].setStartPos(_startPos);
		s[0].setStartDir(RIGHT);
		board[row][col] = EMPTY;

	}
	else if (originalBoard[row][col] == '#')
	{
		s[1].setPosition(row, col);
		_startPos.set(row, col);
		s[1].setStartPos(_startPos);
		s[1].setStartDir(LEFT);
		board[row][col] = EMPTY;
	}
}

void TheSnakesGame::updateLocationInBoard(const Snake * s, const Point& head, const Point& tail)			//ask lecturer how to avoid use of casting
{
	int size, i;
	Point *snakeLoc;
	size = s->getLength();
	snakeLoc = s->getSnakeLoc();
	
	board[tail.getY()][tail.getX()] = EMPTY;

	if (s->getSnakeCurrentDir() == 0)
		board[head.getY()][head.getX()] = HEADUP;
	else if (s->getSnakeCurrentDir() == 1)
		board[head.getY()][head.getX()] = HEADDOWN;
	else if (s->getSnakeCurrentDir() == 2)
		board[head.getY()][head.getX()] = HEADLEFT;
	else if (s->getSnakeCurrentDir() == 3)
		board[head.getY()][head.getX()] = HEADRIGHT;
	else
		board[head.getY()][head.getX()] = SNAKE;

	for (i = 1;i < size;i++)
		board[snakeLoc[i].getY()][snakeLoc[i].getX()] = SNAKE;

	delete[]snakeLoc;
}

void TheSnakesGame::updateLocationInBoard(const Number *n, const Point& MSB, const int length)
{
	int number = n->getNumVal();
	for(int i=0;i<length;i++)
	{
		board[MSB.getY()][MSB.getX() + length - i - 1] = number % 10 + '0';
		number /= 10;
	}
}

void TheSnakesGame::updateLocationInBoard(const Enemy* enemy, const Point& loc, Point &oldLoc)
{
	board[oldLoc.getY()][oldLoc.getX()] = EMPTY;
	if (enemy == nullptr) return;
	board[loc.getY()][loc.getX()] = enemy->getShape();
}

void TheSnakesGame::updateLocationInBoard(Point p, char c)
{
	board[p.getY()][p.getX()] = c;
}

Snake* TheSnakesGame::snakeCollide(const Point& p)
{
	int x=p.getX(), y=p.getY();
	
	if (board[y][x] == SNAKE || board[y][x] == HEADUP || board[y][x] == HEADDOWN || board[y][x] == HEADLEFT || board[y][x] == HEADRIGHT)
	{
		Point pos;
		pos.set(x, y);
		if (s[0].hitByBullet(pos)) return &s[0];
		if (s[1].hitByBullet(pos)) return &s[1];
	}

	return nullptr;
}

int TheSnakesGame::numCollide(const Point& p)
{
	Number *num;

	if (board[p.getY()][p.getX()] - '0' >= 0 && board[p.getY()][p.getX()] - '0' <= 9)
	{
		num = findNumInBoard(p);
		deleteNumFromArray(num);
		return COLLISION_NUM;
	}

	return 0;
		
	
}

bool TheSnakesGame::setBoard(const char * boardToCopy[ROWS])
{
	OpeningScene();
	clearBoard();
	srand(time(NULL));
	for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0;j < COLS;j++)
		{
			originalBoard[i][j] = boardToCopy[i][j];

		}
		originalBoard[i][COLS] = '\0';
	}
	s[0].setArrowKeys(PLAYER1ARROWS);
	s[1].setArrowKeys(PLAYER2ARROWS);
	s[0].setColor(Color::LIGHTGREEN);
	s[1].setColor(Color::YELLOW);
	s[0].setHeadColor(Color::LIGHTBLUE);
	s[1].setHeadColor(Color::LIGHTBLUE);
	s[0].setGame(this);
	s[1].setGame(this);
	s[0].setRec(&rec);
	s[1].setRec(&rec);
	s[0].setDirection(RIGHT);
	s[1].setDirection(LEFT);
	s[0].setShape('@');
	s[1].setShape('#');
	for (int i = 0; i < MAXNUMSONSCREEN; i++)
		nums[i].setGame(this);
//	for (int i = 0; i<maxNumOfMissions; i++)
//		missions[i].init();
	currentMissionID = rand() % maxNumOfMissions;
//	currentMissionID = 11;
	hideCursor();
	if (MainMenu(true) == MainMenu::EXIT)
	{
		clearBoard();
		printMessageFrame();
		return false;
	}
	
	else
		return true;
}

void TheSnakesGame::init()
{


	for (int i = 0;i < ROWS;i++)
	{
		if (i < 4) setTextColor(Color::LIGHTGREY);
		else setTextColor(Color::WHITE);

		for (int j = 0;j < COLS;j++)
		{
			gotoxy(j, i);										//init proccess should draw in console game. not only to initialize the arrays... note that.
			cout << originalBoard[i][j];
			board[i][j] = originalBoard[i][j];
			handleObjectCreationFromBoard(i, j);
		}
		board[i][COLS] = '\0';

	}
	printMenuFrame();
	resetEnemies();
}

int TheSnakesGame::colided(const Point & p)
{
	int a = p.getX(), b = p.getY();
	if (board[p.getY()][p.getX()] == SNAKE || board[p.getY()][p.getX()] == HEADUP || board[p.getY()][p.getX()] == HEADDOWN || board[p.getY()][p.getX()] == HEADLEFT || board[p.getY()][p.getX()] == HEADRIGHT)
		return COLLISION_SNAKE;
	else if (board[p.getY()][p.getX()] - '0' >= 0 && board[p.getY()][p.getX()] - '0' <= 9)
		return COLLISION_NUM;
	else if (board[p.getY()][p.getX()] == BULLET)
		return COLLISION_BULLET;
	else if (board[p.getY()][p.getX()] != EMPTY)
		return COLLISION_ENEMY;
	else
		return 0;

}

int TheSnakesGame::colided(const Point& p, const Enemy* enemyObject)
{

	if (board[p.getY()][p.getX()] == BULLET)
	{

		int check = s[0].killBullet(p);
		if (check == 0)
		{
			check = s[1].killBullet(p);
			if (enemyObject->getShape() != ROW_FLYER) s[1].increaseShots();
		}
		else if (enemyObject->getShape() != ROW_FLYER) s[0].increaseShots();

		s[0].printShotStats();
		s[1].printShotStats();
		return COLLISION_BULLET;

	}
		
	if (enemyObject->getShape() == BULLET)
	{
		if (board[p.getY()][p.getX()] == NUMKILLER || board[p.getY()][p.getX()] == COLUMN_FLYER || board[p.getY()][p.getX()] == ROW_FLYER)
		{
			for (int i = 0; i < NUMOFENEMIES; i++)
				if (Enemies[i] != nullptr)
					if (Enemies[i]->getLoc() == p)
						if (!(Enemies[i]->isBulletProof()))
						{
							if (((Bullet*)(enemyObject))->getShooterShape() == '@')
								s[0].increaseShots();
							else s[1].increaseShots();
							Enemies[i]->die();
						}
						
			s[0].printShotStats();
			s[1].printShotStats();
			return COLLISION_ENEMY;
		}
	}


	return 0;
}


void TheSnakesGame::run()
{
	int counter = 0, dir, snakeWins;
	char key = 0, s1score = 0, s2score = 0;
	bool s1won, s2won, run = true;
	Enemy* bullet=nullptr;
	int maxReplayTime = 0;
	printMenuFrame();
	printPlayerStats();
	missions[currentMissionID].printMission();
	

	do {
		s1won = s2won = false;

		if (key == ESC && !replayMode)
		{
			key = 0;
			PlaySound(TEXT("click.wav"), NULL, SND_FILENAME);
			handleSubMenu(run);
			if (run)
			{
				printMenuFrame();
				printPlayerStats();
				missions[currentMissionID].printMission();
			}
			
		}

		bool gameInput = false;

		if (!replayMode)
		{
			if (_kbhit())
			{
				key = _getch();
				gameInput = true;
				if (key == 'a' || key == 'd' || key == 'w' || key == 's' || key == 'z' || key == 'j' || key == 'i' || key == 'l' || key == 'k' || key == 'n')
					rec.insertAction(time_g, key);
			}
		}
		else
		{
			key = rec.getAction(time_g);
			if (key != '\0') gameInput = true;

		}
			
		if (gameInput)
		{
			if ((dir = s[0].getDirection(key)) != NO_ACTION && s[0].activated())
				s[0].setDirection(dir);
			else if ((dir = s[1].getDirection(key)) != NO_ACTION && s[1].activated())
				s[1].setDirection(dir);
			else if (key == 'z' && s[0].activated()) s[0].shoot();
			else if (key == 'n'&& s[1].activated()) s[1].shoot();
		
		}
		
		setTextColor(WHITE);
		if (run)
		{
			removedeadEnemies();
			moveEnemies();
			s[0].move();
			s[1].move();
			removedeadEnemies();

			Point dummy;

			if (s[0].isDead())
			{
			
				s2won = true;
				s[1].increaseScore();
				s[1].enlargeBody(s[1].getNextHeadPos(), s[1].getTail());
			}
			if (s[1].isDead())
			{
				s1won = true;
				s[0].increaseScore();
				s[0].enlargeBody(s[0].getNextHeadPos(), s[0].getTail());
			}
			Sleep(200);
		}
		
		if (s[0].getScore() > s1score)
			s1won = true;
		if (s[1].getScore() > s2score)
			s2won = true;

		if (counter == NUMPRINTCYCLE - 1)
		{
			counter = 0;
			if (!replayMode)
			{
				
				nums[numsOnScreen].setNumber();				//submerge set functions
				nums[numsOnScreen].setnumberPart2();
				setTextColor(WHITE);
				nums[numsOnScreen].printNumber();
				if (missions[currentMissionID].succeed(nums[numsOnScreen].getNumVal()) && Enemies[4] != nullptr && nums[numsOnScreen].getNumVal()!=-1)
					((NumKiller*)Enemies[4])->insertNewSolution(*(nums[numsOnScreen].getNumberLoc()));
				rec.insertNum(nums[numsOnScreen]);
				numsOnScreen++;

			}
			else
			{
				if (missions[currentMissionID].succeed(nums[numsOnScreen].getNumVal()) && Enemies[4] != nullptr && nums[numsOnScreen].getNumVal() != -1)
					((NumKiller*)Enemies[4])->insertNewSolution(*(nums[numsOnScreen].getNumberLoc()) );

				if (numsOnScreen < endNumsRec && nums[numsOnScreen].getNumVal() != -1)
				{
					nums[numsOnScreen].printNumber();
					numsOnScreen++;;
				}

			}
			
		}
		else
			counter++;

		s1score = s[0].getScore();
		s2score = s[1].getScore();

		bool endOfMission = false;

		time_g++;

		if (s1won || s2won)
		{
			playerWonSeq(s1won, s2won);
			printPlayerStats();
			endOfMission = true;

		}
		
		else if (numsOnScreen == MAXNUMSONSCREEN)
		{
			markPossibleSolutions();
			endOfMission = true;
		}
		

		if (time_g >= maxReplayTime && replayMode)
			endOfMission = true;
		
		
		
	
		if (endOfMission)
		{
			NewMissionNotice(run);

			if (!replayMode && run)
			{
				missionEnd = false;
				currentMissionID = rand() % maxNumOfMissions;
				setNewMission();
				counter = 0;
			}
			else if (replayMode)
			{
				maxReplayTime = time_g;
				counter = 0;
				loadPreviousPlayerStats(s1won, s2won);
				setBoardForReplay();
				
				
			}

		}

	} while (run && s1score<WINNINGSCORE && s2score<WINNINGSCORE);

	clearBoard();
	printMessageFrame();

	if (s1score == WINNINGSCORE)
	{
		snakeWins = 1;
		printWinningMessage(snakeWins);
	}
	else if (s2score == WINNINGSCORE)
	{
		snakeWins = 2;
		printWinningMessage(snakeWins);
	}

	s[0].freeSnake();
	s[1].freeSnake();
	gotoxy(27, 11);
	setTextColor(WHITEONBLUE);

}

void TheSnakesGame::printVirtaulBoard()			//function for the sake of debugging
{
	int j;
	system("cls");
	for (j = 0;j < 24;j++)
		printf("%s", board[j]);
}

Number* TheSnakesGame::findNumInBoard(const Point& headNext)
{
	for (int i = 0; i < numsOnScreen; i++)
		if (nums[i].doesIncludeThePoint(headNext))
			return &(nums[i]);

	return NULL;
}

void TheSnakesGame::deleteNumFromArray(Number *num)
{
	bool isFound = false;
	int i;
	
	if (num->getNumVal() == -1) return;

	Point *numLoc = num->getNumberLoc();


	if (missions[currentMissionID].succeed(num->getNumVal()) && Enemies[4] != nullptr)
	{
		Point Up, Down, Left, Right, numLoc;																	// Adjust NumKiller location deviation casued by the double move
		Up.set(Enemies[4]->getLoc().getX(), Enemies[4]->getLoc().getY()-1);
		Down.set(Enemies[4]->getLoc().getX(), Enemies[4]->getLoc().getY()+1);
		Left.set(Enemies[4]->getLoc().getX()-1, Enemies[4]->getLoc().getY());
		Right.set(Enemies[4]->getLoc().getX()+1, Enemies[4]->getLoc().getY());
		numLoc = *(num->getNumberLoc());

		if (numLoc == ((NumKiller*)Enemies[4])->getDest() && (numLoc == Up || numLoc == Down || numLoc == Left || numLoc == Right))
		{
			updateLocationInBoard(*(num->getNumberLoc()), EMPTY);
			Enemies[4]->setLoc(*(num->getNumberLoc()));
			updateLocationInBoard(Enemies[4]->getLoc(), Enemies[4]->getShape());
			setTextColor(Enemies[4]->getColor());
			Enemies[4]->getLoc().draw(Enemies[4]->getShape());													// 
		}
			
		((NumKiller*)Enemies[4])->deleteSolution(*(num->getNumberLoc()));
	}
		

	gotoxy(numLoc[0].getX(), numLoc[0].getY());
	setTextColor(Color::LIGHTMAGENTA);
	num->printNumber();
	Sleep(60);

	for (int k = 0; k < num->getNumLen(); k++)
	{
		gotoxy(numLoc[k].getX(), numLoc[k].getY());
		cout << EMPTY;
		board[numLoc[k].getY()][numLoc[k].getX()] = EMPTY;
		setTextColor(Color::WHITE);
	}


	for(i=0;!isFound && i<numsOnScreen;i++)
	{
		if (nums[i].doesIncludeThePoint(numLoc[0]))
			isFound = true;
	}
	i--;
	num->deleteNumber();
	nums[i] = nums[numsOnScreen-1];
	numsOnScreen--;

	delete[]numLoc;
}

Snake* TheSnakesGame::getSecondSnake(const Snake *snake1)
{
	Point *snake1Loc = snake1->getSnakeLoc();
	Point *s1 = s[0].getSnakeLoc();
	Snake* res;

	if (snake1Loc[0].getX() == s1[0].getX() && snake1Loc[0].getY() == s1[0].getY())
		res = &s[1];
	else
		res = &s[0];

	delete[]snake1Loc;
	delete[]s1;

	return res;
}

void TheSnakesGame::playerWonSeq(bool s1won, bool s2won)
{
	char player[9];
	Color color;
	bool dummy = true;

	if (s1won)
	{
		sprintf_s(player, "Player 1");
		color = LIGHTGREENONBLUE;
	}
	else
	{
		sprintf_s(player, "Player 2");
		color = YELLOWONBLUE;
	}

	gotoxy(1, 2); 
	setTextColor(color);
	cout << player;
	setTextColor(WHITEONBLUE);
	cout << " wins the current Mission!! aaaamazing!";
			
	printPlayerStats();

}

void TheSnakesGame::remove_X_NumsOfBoard(int X)
{
	int initDelay;
	if (X <= MAXNUMSONSCREEN / 2)
		initDelay = 300;
	else
		initDelay = 400;

	for (int i = X; X < numsOnScreen&&i >= 0; i--)
	{
		int j = i;
		deleteNumFromArray(&nums[i]);
		if (i<45) Sleep(initDelay - 10 * j);
	}

	
}

bool TheSnakesGame::checkMissionSuccess(Snake& s, const Point& headNext, const Point& oldTail)		
{
	Number *num = findNumInBoard(headNext);
	bool res;
	Snake* other;
	Point otherHeadNext, otherOldTail;

	
	res = missions[currentMissionID].succeed(num->getNumVal());
		
	if (res)
		s.enlargeBody(headNext, oldTail);
	else
	{
		for (int i = 0; i < 2; i++)
		{
			if (TheSnakesGame::s[i].getShape() != s.getShape())
			{
				other = TheSnakesGame::s + i;
				otherHeadNext = other->getNextHeadPos();
				otherOldTail = other->getTail();
				other->enlargeBody(otherHeadNext, otherOldTail);
			}		
		}
	}

	if (res) PlaySound(TEXT("snakeWin"), NULL, SND_FILENAME);
	else PlaySound(TEXT("snakeLose"), NULL, SND_FILENAME);
	deleteNumFromArray(num);

	return res;
}

void TheSnakesGame::markPossibleSolutions()
{
	bool found = false;

	for (int i = 0; i < numsOnScreen; i++)
	{
		
		if (missions[currentMissionID].succeed(nums[i].getNumVal()))
			found = true;
	}
	
	gotoxy(1, 2);
	setTextColor(WHITEONBLUE);
	cout << "The mission ended in a tie!";
	PlaySound(TEXT("tie.wav"), NULL, SND_FILENAME);

	if (!found)
	{
		setTextColor(WHITEONBLUE);
		cout << " No possible solutions but good effort!";
		Sleep(200);
		return;
	}

	for (int j = 0; j < 8; j++)
	{
		bool dummy = true;
		mark_numbers(LIGHTMAGENTA);
		mark_numbers(BLACK);
	}	

	for (int i = 0; i < numsOnScreen; i++)
	{
		setTextColor(WHITE);
		nums[i].printNumber();
	}
}

void TheSnakesGame::printInstructions()
{
	clearBoard();
	setTextColor(Color::LIGHTGREY);;
	gotoxy(0, 4);
	cout << "Each player controls a snake. The game will present different missions\non the screen";
	cout << " and numbers will appear in random locations.\nIn each mission, the player who collects a correct number first \nwins the mission,";
	cout << " gains a point and increases in length.\n";
	cout << "If a player collects a wrong number the other player gains a point\nand increases in length.\n";
	setTextColor(Color::BROWN);;
	cout << "The first player to reach 12 points wins the game!";

	setTextColor(Color::LIGHTGREEN);
	gotoxy(15, 14); //(15,10)
	cout << "Player 1";
	setTextColor(Color::LIGHTBLUE);
	gotoxy(7, 18); //(7,14)
	cout << "(LEFT) = a " << " ";
	setTextColor(Color::LIGHTMAGENTA);
	cout << " d = (RIGHT)";
	setTextColor(Color::LIGHTRED);
	gotoxy(15, 16); //(15,12)
	cout << "(UP) = w";
	setTextColor(Color::LIGHTCYAN);
	gotoxy(14, 20); //(14,16)
	cout << "(DOWN) = s";
	setTextColor(Color::LIGHTGREY);
	gotoxy(13, 23);
	cout << "(SHOOT) =  z";

	setTextColor(Color::YELLOW);
	gotoxy(55, 14);
	cout << "Player 2";
	setTextColor(Color::LIGHTBLUE);
	gotoxy(47, 18);
	cout << "(LEFT) = j " << " ";
	setTextColor(Color::LIGHTMAGENTA);
	cout << " l = (RIGHT)";
	setTextColor(Color::LIGHTRED);
	gotoxy(55, 16);
	cout << "(UP) = i";
	setTextColor(Color::LIGHTCYAN);
	gotoxy(54, 20);
	cout << "(DOWN) = k";
	setTextColor(Color::LIGHTGREY);
	gotoxy(53, 23);
	cout << "(SHOOT) =  n";
}

void TheSnakesGame::printMenuFrame()
{
	gotoxy(0, 0);
	setTextColor(Color::DARKGREY_BACK);
	cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"; // 0
	cout << "|                                                                              |"; // 1
	cout << "|                                                                              |";	// 2
	cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"; // 3

	setTextColor(Color::BLUE_BACK);
	gotoxy(1, 1);
	cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";   // 1
	gotoxy(1, 2);
	cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";   // 1

	setTextColor(Color::WHITE);
}

void TheSnakesGame::printMessageFrame()
{
	setTextColor(Color::DARKGREY_BACK);
	gotoxy(25, 9);
	cout << "|||||||||||||||||||||||||||||||||||";
	gotoxy(25, 10);
	cout << "|                                 |";
	gotoxy(25, 11);
	cout << "|                                 |";
	gotoxy(25, 12);
	cout << "|||||||||||||||||||||||||||||||||||";

	setTextColor(Color::BLUE_BACK);
	gotoxy(26, 10);
	cout << "                                 ";
	gotoxy(26, 11);
	cout << "                                 ";


	setTextColor(Color::WHITEONBLUE);
}

void TheSnakesGame::handleSubMenu(bool &run_flag)
{
	if (replayMode) return;
	int menuChoice;

	menuChoice = SubMenu();

	if (menuChoice == SubMenu::Exit)
		run_flag = false;
	else if (menuChoice == SubMenu::GoToMM)
	{
		system("cls");
		if (MainMenu(false) == MainMenu::BeginGame)
			menuChoice = SubMenu::RestartG;
		else run_flag = false;                       // EXIT SELECTED
						
	}
	else if (menuChoice == SubMenu::Resume)
	{
		printMenuFrame();
		gotoxy(1, 1);
		missions[currentMissionID].printMission();
	}
	else if (menuChoice == SubMenu::RestartM)
		setNewMission();
	else if (menuChoice == SubMenu::NewM)
	{
		currentMissionID = rand() % maxNumOfMissions;
		setNewMission();
	}
	
	if (menuChoice == SubMenu::RestartG)
	{
		numsOnScreen = 0;
		s[0].reset();
		s[1].reset();
		s[0].setDirection(RIGHT);
		s[1].setDirection(LEFT);
	
		init();
		currentMissionID = rand() % maxNumOfMissions;
		printMenuFrame();
		missions[currentMissionID].printMission();
	}



	if (menuChoice==SubMenu::Replay && !replayMode)
		replayMode = true;

	
}

void TheSnakesGame::printWinningMessage(int player_ref)
{
	if (player_ref == 1)
	{
		gotoxy(30, 10);
		setTextColor(Color::LIGHTGREENONBLUE);
		cout << "Player " << player_ref;
		setTextColor(Color::WHITEONBLUE);
		cout << " wins the game!";

	}
	else if (player_ref == 2)
	{
		gotoxy(30, 10);
		setTextColor(Color::YELLOWONBLUE);
		cout << "Player " << player_ref;
		setTextColor(Color::WHITEONBLUE);
		cout << " wins the game!";
	}
}

void TheSnakesGame::clearBoard()
{
	gotoxy(0, GAME_TOP_MARGINE);
	setTextColor(WHITE);
	for (int i = 0; i < ROWS- GAME_TOP_MARGINE; i++)
		cout << "                                                                                ";
}



void TheSnakesGame::printPlayerStats()
{
	setTextColor(LIGHTGREY_BACK);
	gotoxy(65, 0);
	cout << "|||||||||||||||";
	gotoxy(65, 3);
	cout << "|||||||||||||||";

	gotoxy(65, 1);
	cout << "||";
	gotoxy(65, 2);
	cout << "||";
	gotoxy(78, 1);
	cout << "||";
	gotoxy(78, 2);
	cout << "||";


	setTextColor(DARKGREY_BACK);
	gotoxy(65, 0);
	cout << "|";
	gotoxy(65, 1);
	cout << "|";
	gotoxy(65, 2);
	cout << "|";
	gotoxy(65, 3);
	cout << "|";

	gotoxy(79, 0);
	cout << "|";
	gotoxy(79, 1);
	cout << "|";
	gotoxy(79, 2);
	cout << "|";
	gotoxy(79, 3);
	cout << "|";
	

	gotoxy(67, 1);
	setTextColor(MAGENTA_BACK);
	cout << "|||||||||||";
	gotoxy(67, 2);
	cout << "|||||||||||";

	setTextColor(LIGHTGREY_BACK);
	gotoxy(72, 1);
	cout << "|";
	gotoxy(72, 2);
	cout << "|";

	setTextColor(WHITEONMAGENTA);
	gotoxy(67, 1);
	cout << "SHOTS";

	setTextColor(WHITEONMAGENTA);
	gotoxy(73, 1);
	cout << "SCORE";

	gotoxy(75, 2);
	cout << "|";
	gotoxy(69, 2);
	cout << "|";


	int k = s[1].getScore();
    if (k <=9) gotoxy(77, 2);
	else gotoxy(76, 2);
	setTextColor(YELLOWONMAGENTA);
	cout << k;
	gotoxy(71, 2);
	cout << s[1].getShots();

	k = s[0].getScore();
	setTextColor(LIGHTGREENONMAGENTA);
	gotoxy(73, 2);
	cout << k;
	gotoxy(67, 2);
	cout << s[0].getShots();

}

void TheSnakesGame::mark_numbers(Color color)
{

	for (int i = 0; i < numsOnScreen; i++)
	{
		if (missions[currentMissionID].succeed(nums[i].getNumVal()))
		{
			setTextColor(color);
			nums[i].printNumber();
		}
		
	}

	Sleep(200);
}

void TheSnakesGame::setNewMission()
{
	rec.resetIndices();
	rec.deleteRecords();
	replayMode = false;
//	rec.printActionsArr();
	s[0].newScreen();
	s[0].setReplayMode(false);
	s[1].newScreen();
	s[1].setReplayMode(false);

	resetEnemies();
	remove_X_NumsOfBoard(numsOnScreen / 2);
	rec.recordInitNums(numsOnScreen, nums);
	printMenuFrame();
	printPlayerStats();
	missions[currentMissionID].printMission();
	updateNumKiller();
	
//	rec.setInitNums(numsOnScreen, nums);
	time_g = 0;

}

Point* TheSnakesGame::getDetValidPosInBoard()		//	don't forget to delete the returned value after each use of this function
{
	int i, j;
	Point* res = new Point;
	for(i=GAME_TOP_MARGINE;i<ROWS;i++)
		for(j=GAME_LEFT_MARGINE;j<COLS;j++)
		{
			if (board[i][j] == EMPTY || (board[i][j] >= '0'&&board[i][j] <= '9'))
			{
				res->set(j, i);
				return res;
			}
		}

	return nullptr;
}

Point* TheSnakesGame::getValidPosInBoard()		//	don't forget to delete the returned value after each use of this function
{
	int i, j;
	Point* res = new Point;
	Number* tmp;
	bool isFound = false;
	do
	{
		i = rand() % ROWS + GAME_TOP_MARGINE;
		j = rand() % COLS + GAME_LEFT_MARGINE;
		if (board[i][j] == EMPTY || (board[i][j] >= '0'&&board[i][j] <= '9'))
		{
			res->set(j, i);
			isFound = true;
			if (board[i][j] >= '0'&&board[i][j] <= '9')
			{
				tmp = findNumInBoard(*res);
				deleteNumFromArray(tmp);
			}
			return res;
		}
	} while (!isFound);
	
	return nullptr;
}

// FREE ALLOCATIONS
void TheSnakesGame::setEnemies()
{
	Point p;
	p.set(30, 23);
	Enemies = new Enemy*[NUMOFENEMIES];

	for (int i = 0; i < NUMOFENEMIES; i++) Enemies[i] = nullptr;

	Enemies[0] = new Flyer(p, ROW_FLYER, RIGHT, false, LIGHTGREEN, HORIZONTAL, this);
	p.set(50, 15);
	Enemies[1] = new Flyer(p, ROW_FLYER, LEFT, true, LIGHTGREEN, HORIZONTAL, this);
	p.set(45, 23);
	Enemies[2] = new Flyer(p, COLUMN_FLYER, UP, true, LIGHTBLUE, VERTICAL, this);
	p.set(55, 15);
	Enemies[3] = new Flyer(p, COLUMN_FLYER, DOWN, false, LIGHTBLUE, VERTICAL, this);
	p.set(10, 19);
	Enemies[4] = new NumKiller(p, '%', LIGHTMAGENTA, this);

}

void TheSnakesGame::resetEnemies()
{
	setTextColor(WHITE);

	if (Enemies != nullptr)
	{
		for (int i = 0; i < NUMOFENEMIES; i++)
			if (Enemies[i] != nullptr)
			{
				int xLoc = Enemies[i]->getLoc().getX(), yLoc = Enemies[i]->getLoc().getY();
				gotoxy(xLoc, yLoc);
				cout << EMPTY;
				updateLocationInBoard(Enemies[i]->getLoc(), EMPTY);
				delete Enemies[i];
			}
		

		delete Enemies;

	}
	
	setEnemies();
}

void TheSnakesGame::moveEnemies()
{
	for (int i = 0; i < NUMOFENEMIES; i++)
		if (Enemies[i] != nullptr) Enemies[i]->move();
}

void TheSnakesGame::removedeadEnemies()
{
	for (int i = 0; i < NUMOFENEMIES; i++)
	{
		if(Enemies[i] !=nullptr)
			if (Enemies[i]->isDead())
			{
				delete Enemies[i];
				Enemies[i] = nullptr;
			}
	}
}

void TheSnakesGame::updateNumKiller()
{
	if (Enemies[4] == nullptr)  return;

	Point* res = nullptr;
	int size = 0;

	for (int i = 0; i < numsOnScreen; i++)
	{
		if (missions[currentMissionID].succeed(nums[i].getNumVal()))
			size++;
	}

	if (size > 0)
	{
		res = new Point[size];

		for (int i = 0, j=0; i < numsOnScreen; i++)
		{
			if (missions[currentMissionID].succeed(nums[i].getNumVal()))
			{
				res[j] = *(nums[i].getNumberLoc());
				j++;
			}
				
		}
	}
	
	((NumKiller*)Enemies[4])->updateSolutions(res, size);

}

void TheSnakesGame::setBoardForReplay()
{


	time_g = 0;
	replayMode = true;

	init();
	rec.getNumsArr(nums, startNumsRec, endNumsRec);
	for (int i = 0; i < startNumsRec; i++)
	{
		if (nums[i].getNumVal()!=-1)
			nums[i].printNumber();
		else 
		{
			startNumsRec--;
			break;

		}
		
		

	}
		

	numsOnScreen = startNumsRec;

	rec.resetIndices();
	s[0].newScreen();
	s[1].newScreen();
	s[0].setReplayMode(true);
	s[1].setReplayMode(true);
	missions[currentMissionID].printMission();
	printPlayerStats();
	resetEnemies();
	updateNumKiller();
	Enemies[4]->setDirection(STOP);

	
	
	
}



void TheSnakesGame::loadPreviousPlayerStats(bool _s1won, bool _s2won)
{
	if (_s1won)
	{
		s[0].shrinkBody();
		s[0].decreaseScore();
	}
	if (_s2won)
	{
		s[1].shrinkBody();
		s[1].decreaseScore();
	}

}

void TheSnakesGame::NewMissionNotice(bool _runflag)
{
	missionEnd = true;
	gotoxy(28, 3);
	setTextColor(BLACKONGREY);
	cout << "New mission in: ";
	
	for (int i = 0; i < 5; i++)
	{
		gotoxy(47, 3);
		setTextColor(BLACKONGREY);
		cout << 5 - i;

		if (_kbhit() && !replayMode)
		{
			char key = _getch();

			if (key == ESC)
			{
				PlaySound(TEXT("click.wav"), NULL, SND_FILENAME);
				handleSubMenu(_runflag);
				if (_runflag)
				{
					printMenuFrame();
					printPlayerStats();
					missions[currentMissionID].printMission();
					gotoxy(28, 3);
					setTextColor(BLACKONGREY);
					cout << "New mission in: ";
					gotoxy(47, 3);
					setTextColor(BLACKONGREY);
					cout << 5 - i;
				}

				if (!_runflag || replayMode)
				{
					if (_runflag) replayMode = true;
					return;
				}
				
		
			}
				
		}

		Sleep(1000);
	}

	replayMode = false;
}


void TheSnakesGame::loadMissions()
{
	char* description = new char[MAXCHARSONSTRING];

	ifstream missionsFile("Missions.txt");
	if (!missionsFile.is_open()) return;

	char s[3];
	missionsFile.getline(s, 3);
	maxNumOfMissions = atoi(s);


	for (int i=0; i<maxNumOfMissions; i++)
	{

		missionsFile.getline(description, MAXCHARSONSTRING);
		missions[i].setMission(description);
		
	}

	delete description;
	missionsFile.close();

	

}


