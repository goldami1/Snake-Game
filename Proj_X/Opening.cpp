#include "Opening.h"



void OpeningScene()
{

#define TIMER 25
#define S_LOOPCYCLE 16

	hideCursor();

#define  BUFFER 8
#define  MID 8


	int line1_x = 7, line2_x = 24, set1_y = 7, set2_y = 10, set1_line2_y = set1_y + 8, set2_line2_y = 8;
	int positions[] = { 0,7,14,22, 27, 36, 41, 48, 55 };
	int x1 = 7, y1 = 7, x2 = 24, y2 = y1 + 8;
	int pos = 0, s2xpos = 65, s1xpos = 29;
	Point s1[35] = { { 5,22 },{ 6,22 },{ 7, 22 },{ 8, 22 },{ 9, 22 },{ 10, 22 },{ 10, 21 },{ 10,20 },{ 10,19 },{ 9,19 },{ 8, 19 },{ 7,19 },{ 7,18 },{ 7,17 },{ 7,16 },{ 8, 16 },{ 9,16 },{ 9,17 },{ 9,18 },{ 10,18 },{ 10, 17 },{ 10, 16 },{ 10,15 },{ 10,14 },{ 10,13 },{ 9, 13 },{ 8,13 },{ 7,13 },{ 6, 13 },{ 5,13 },{ 4,13 },{ 3,13 },{ 2, 13 },{ 1,13 },{ 0,13 } };
	Point s2[35] = { { 76, 14 },{ 76, 13 },{ 76, 12 },{ 76, 11 },{ 76,10 },{ 76,9 },{ 76,8 },{ 76, 7 },{ 76, 6 },{ 76, 5 },{ 76, 4 },{ 76,3 },{ 75,3 },{ 74,3 },{ 73,3 },{ 72,3 },{ 71,3 },{ 70,3 },{ 69,3 },{ 68,3 },{ 67,3 },{ 66,3 },{ 65,3 },{ 64,3, },{ 63,3 },{ 62,3 },{ 61,3 },{ 61, 4 },{ 61,5 },{ 60, 5 },{ 60, 4 },{ 60, 3 },{ 60, 2 },{ 60, 1 },{ 60,0 } };

	setTextColor(Color::WHITE);




	PlaySound(TEXT("dash.wav"), NULL, SND_FILENAME);
	for (int i = 0; i < 10; i++)
	{
		setTextColor(Color::LIGHTGREY);

		gotoxy(pos, y1);
		cout << "     ";
		gotoxy(pos, y1 + 1);
		cout << "     ";
		gotoxy(pos, y1 + 2);
		cout << "     ";
		gotoxy(pos, y1 + 3);
		cout << "     ";
		gotoxy(pos, y1 + 4);
		cout << "     ";

		pos = i * 7;
		if (pos == 63) pos = 65;


		gotoxy(pos, y1);
		cout << " ||||";
		gotoxy(pos, y1 + 1);
		cout << "||   ";
		gotoxy(pos, y1 + 2);
		cout << "  || ";
		gotoxy(pos, y1 + 3);
		cout << "   ||";
		gotoxy(pos, y1 + 4);
		cout << "|||| ";

		Sleep(TIMER);
	}

	pos = 0;
	for (int i = 0; i < 9; i++)
	{

		setTextColor(Color::LIGHTGREY);

		gotoxy(pos, y1);
		cout << "     ";
		gotoxy(pos, y1 + 1);
		cout << "     ";
		gotoxy(pos, y1 + 2);
		cout << "     ";
		gotoxy(pos, y1 + 3);
		cout << "     ";
		gotoxy(pos, y1 + 4);
		cout << "     ";

		pos = i * 7;
		if (pos == 56) pos = 59;

		gotoxy(pos, y1);
		cout << "|||||";
		gotoxy(pos, y1 + 1);
		cout << "||   ";
		gotoxy(pos, y1 + 2);
		cout << "|||||";
		gotoxy(pos, y1 + 3);
		cout << "||   ";
		gotoxy(pos, y1 + 4);
		cout << "|||||";

		Sleep(TIMER);
	}

	if (_kbhit())
	{
		int ch = _getch();
		if (ch == ESC) return;
	}
	pos = 0;
	for (int i = 0; i < 8; i++)
	{
		setTextColor(Color::LIGHTGREY);

		gotoxy(pos, y1);
		cout << "      ";
		gotoxy(pos, y1 + 1);
		cout << "      ";
		gotoxy(pos, y1 + 2);
		cout << "      ";
		gotoxy(pos, y1 + 3);
		cout << "      ";
		gotoxy(pos, y1 + 4);
		cout << "      ";

		pos = i * 7;
		if (pos == 49) pos = 52;

		gotoxy(pos, y1);
		cout << "||  ||";
		gotoxy(pos, y1 + 1);
		cout << "||||  ";
		gotoxy(pos, y1 + 2);
		cout << "||||  ";
		gotoxy(pos, y1 + 3);
		cout << "|| || ";
		gotoxy(pos, y1 + 4);
		cout << "||  ||";

		Sleep(TIMER);
	}



	pos = 0;
	for (int i = 0; i < 7; i++)
	{

		setTextColor(Color::LIGHTGREY);
		gotoxy(pos, y1);
		cout << "        ";
		gotoxy(pos, y1 + 1);
		cout << "        ";
		gotoxy(pos, y1 + 2);
		cout << "        ";
		gotoxy(pos, y1 + 3);
		cout << "        ";
		gotoxy(pos, y1 + 4);
		cout << "        ";

		pos = i * 7;

		gotoxy(pos, y1);
		cout << "    ||   ";
		gotoxy(pos, y1 + 1);
		cout << "   ||||  ";
		gotoxy(pos, y1 + 2);
		cout << "   |  |  ";
		gotoxy(pos, y1 + 3);
		cout << "  |||||| ";
		gotoxy(pos, y1 + 4);
		cout << " ||    ||";

		Sleep(TIMER);
	}


	pos = 0;
	for (int i = 0; i < 6; i++)
	{

		setTextColor(Color::LIGHTGREY);
		gotoxy(pos, y1);
		cout << "       ";
		gotoxy(pos, y1 + 1);
		cout << "       ";
		gotoxy(pos, y1 + 2);
		cout << "       ";
		gotoxy(pos, y1 + 3);
		cout << "       ";
		gotoxy(pos, y1 + 4);
		cout << "       ";

		pos = i * 7;

		gotoxy(pos, y1);
		cout << "||   ||";
		gotoxy(pos, y1 + 1);
		cout << "|||  ||";
		gotoxy(pos, y1 + 2);
		cout << "|| | ||";
		gotoxy(pos, y1 + 3);
		cout << "||  |||";
		gotoxy(pos, y1 + 4);
		cout << "||   ||";

		Sleep(TIMER);
	}

	if (_kbhit())
	{
		int ch = _getch();
		if (ch == ESC) return;
	}
	pos = 0;
	for (int i = 0; i < 5; i++)
	{

		setTextColor(Color::LIGHTGREY);
		gotoxy(pos, y1);
		cout << "     ";
		gotoxy(pos, y1 + 1);
		cout << "     ";
		gotoxy(pos, y1 + 2);
		cout << "     ";
		gotoxy(pos, y1 + 3);
		cout << "     ";
		gotoxy(pos, y1 + 4);
		cout << "     ";

		pos = i * 7;
		if (pos == 28) pos = 29;

		gotoxy(pos, y1);
		cout << " ||||";
		gotoxy(pos, y1 + 1);
		cout << "||   ";
		gotoxy(pos, y1 + 2);
		cout << "  || ";
		gotoxy(pos, y1 + 3);
		cout << "   ||";
		gotoxy(pos, y1 + 4);
		cout << "|||| ";

		Sleep(TIMER);
	}

	pos = 0;
	for (int i = 0; i < 4; i++)
	{

		setTextColor(Color::LIGHTGREY);
		gotoxy(pos, y1);
		cout << "     ";
		gotoxy(pos, y1 + 1);
		cout << "     ";
		gotoxy(pos, y1 + 2);
		cout << "     ";
		gotoxy(pos, y1 + 3);
		cout << "     ";
		gotoxy(pos, y1 + 4);
		cout << "     ";

		pos = i * 7;

		gotoxy(pos, y1);
		cout << "|||||";
		gotoxy(pos, y1 + 1);
		cout << "||   ";
		gotoxy(pos, y1 + 2);
		cout << "|||||";
		gotoxy(pos, y1 + 3);
		cout << "||   ";
		gotoxy(pos, y1 + 4);
		cout << "|||||";

		Sleep(TIMER);
	}

	if (_kbhit())
	{
		int ch = _getch();
		if (ch == ESC) return;
	}
	pos = 0;
	for (int i = 0; i < 3; i++)
	{

		setTextColor(Color::LIGHTGREY);
		gotoxy(pos, y1);
		cout << "      ";
		gotoxy(pos, y1 + 1);
		cout << "      ";
		gotoxy(pos, y1 + 2);
		cout << "      ";
		gotoxy(pos, y1 + 3);
		cout << "      ";
		gotoxy(pos, y1 + 4);
		cout << "      ";

		pos = i * 7;


		gotoxy(pos, y1);
		cout << "||  ||";
		gotoxy(pos, y1 + 1);
		cout << "||  ||";
		gotoxy(pos, y1 + 2);
		cout << "||||||";
		gotoxy(pos, y1 + 3);
		cout << "||  ||";
		gotoxy(pos, y1 + 4);
		cout << "||  ||";

		Sleep(TIMER);
	}

	pos = 0;
	for (int i = 0; i < 2; i++)
	{
		setTextColor(Color::LIGHTGREY);
		gotoxy(pos, y1);
		cout << "      ";
		gotoxy(pos, y1 + 1);
		cout << "      ";
		gotoxy(pos, y1 + 2);
		cout << "      ";
		gotoxy(pos, y1 + 3);
		cout << "      ";
		gotoxy(pos, y1 + 4);
		cout << "      ";

		pos = i * 7;

		gotoxy(pos, y1);
		cout << "||||||";
		gotoxy(pos, y1 + 1);
		cout << "  ||  ";
		gotoxy(pos, y1 + 2);
		cout << "  ||  ";
		gotoxy(pos, y1 + 3);
		cout << "  ||  ";
		gotoxy(pos, y1 + 4);
		cout << "  ||  ";

		Sleep(TIMER);
	}

	if (_kbhit())
	{
		int ch = _getch();
		if (ch == ESC) return;
	}

	setTextColor(Color::LIGHTMAGENTA);

	gotoxy(line2_x, set1_line2_y);
	cout << "                           |||||";
	gotoxy(line2_x, set1_line2_y + 1);
	cout << "                           ||   ";
	gotoxy(line2_x, set1_line2_y + 2);
	cout << "                           |||||";
	gotoxy(line2_x, set1_line2_y + 3);
	cout << "                           ||   ";
	gotoxy(line2_x, set1_line2_y + 4);
	cout << "                           |||||";

	Sleep(80);
	gotoxy(line2_x, set1_line2_y);
	cout << "                ||||  |||| |||||";
	gotoxy(line2_x, set1_line2_y + 1);
	cout << "                ||  ||  || ||   ";
	gotoxy(line2_x, set1_line2_y + 2);
	cout << "                ||  ||  || |||||";
	gotoxy(line2_x, set1_line2_y + 3);
	cout << "                ||  ||  || ||   ";
	gotoxy(line2_x, set1_line2_y + 4);
	cout << "                ||      || |||||";

	if (_kbhit())
	{
		int ch = _getch();
		if (ch == ESC) return;
	}

	Sleep(80);
	gotoxy(line2_x, set1_line2_y);
	cout << "          ||    ||||  |||| |||||";
	gotoxy(line2_x, set1_line2_y + 1);
	cout << "         ||||   ||  ||  || ||   ";
	gotoxy(line2_x, set1_line2_y + 2);
	cout << "         |  |   ||  ||  || |||||";
	gotoxy(line2_x, set1_line2_y + 3);
	cout << "        ||||||  ||  ||  || ||   ";
	gotoxy(line2_x, set1_line2_y + 4);
	cout << "       ||    || ||      || |||||";

	Sleep(80);
	gotoxy(line2_x, set1_line2_y);
	cout << "||||||    ||    ||||  |||| |||||";
	gotoxy(line2_x, set1_line2_y + 1);
	cout << "||       ||||   ||  ||  || ||   ";
	gotoxy(line2_x, set1_line2_y + 2);
	cout << "|| ||||  |  |   ||  ||  || |||||";
	gotoxy(line2_x, set1_line2_y + 3);
	cout << "||  ||  ||||||  ||  ||  || ||   ";
	gotoxy(line2_x, set1_line2_y + 4);
	cout << "|||||| ||    || ||      || |||||";

	if (_kbhit())
	{
		int ch = _getch();
		if (ch == ESC) return;
	}

	int pointIndex = 0, counter = 0, ind = 0;
	bool goUp = true;

	PlaySound(TEXT("pop.wav"), NULL, SND_FILENAME);
	for (int i = 0, pos = 0; i < S_LOOPCYCLE * 6; i++)
	{



		setTextColor(Color::LIGHTRED);

		gotoxy(s2xpos, y1 - pos);
		cout << "     ";
		gotoxy(s2xpos, y1 + 1 - pos);
		cout << "     ";
		gotoxy(s2xpos, y1 + 2 - pos);
		cout << "     ";
		gotoxy(s2xpos, y1 + 3 - pos);
		cout << "     ";
		gotoxy(s2xpos, y1 + 4 - pos);
		cout << "     ";

		gotoxy(s1xpos, y1 - pos);
		cout << "     ";
		gotoxy(s1xpos, y1 + 1 - pos);
		cout << "     ";
		gotoxy(s1xpos, y1 + 2 - pos);
		cout << "     ";
		gotoxy(s1xpos, y1 + 3 - pos);
		cout << "     ";
		gotoxy(s1xpos, y1 + 4 - pos);
		cout << "     ";


		if (_kbhit())
		{
			int ch = _getch();
			if (ch == ESC) {
				return;
			}
		}
		if (goUp) pos += 1; else pos -= 1;
		if (pos == 2)
			goUp = false;


		if (pos == -2) goUp = true;

		gotoxy(s2xpos, y1 - pos);
		cout << " ||||";
		gotoxy(s2xpos, y1 + 1 - pos);
		cout << "||   ";
		gotoxy(s2xpos, y1 + 2 - pos);
		cout << "  || ";
		gotoxy(s2xpos, y1 + 3 - pos);
		cout << "   ||";
		gotoxy(s2xpos, y1 + 4 - pos);
		cout << "|||| ";

		setTextColor(Color::LIGHTRED);

		gotoxy(s1xpos, y1 - pos);
		cout << " ||||";
		gotoxy(s1xpos, y1 + 1 - pos);
		cout << "||   ";
		gotoxy(s1xpos, y1 + 2 - pos);
		cout << "  || ";
		gotoxy(s1xpos, y1 + 3 - pos);
		cout << "   ||";
		gotoxy(s1xpos, y1 + 4 - pos);
		cout << "|||| ";

		if (counter % 2 == 0)
		{
			setTextColor(WHITE);

			if (pointIndex >= 10 && pointIndex < 45)
			{
				gotoxy(s1[pointIndex - 10].getX(), s1[pointIndex - 10].getY());
				cout << " ";
				gotoxy(s2[pointIndex - 10].getX(), s2[pointIndex - 10].getY());
				cout << " ";
			}

			if (pointIndex < 35)
			{
				gotoxy(s1[pointIndex].getX(), s1[pointIndex].getY());
				setTextColor(LIGHTBLUE);
				cout << "@";

				if (pointIndex > 0)
				{
					gotoxy(s1[pointIndex - 1].getX(), s1[pointIndex - 1].getY());
					setTextColor(LIGHTGREEN);
					cout << "@";
				}

					gotoxy(s2[pointIndex].getX(), s2[pointIndex].getY());
					setTextColor(LIGHTBLUE);
					cout << "#";

					if (pointIndex > 0)
					{
						gotoxy(s2[pointIndex - 1].getX(), s2[pointIndex - 1].getY());
						setTextColor(YELLOW);
						cout << "@";
					}
			}

			pointIndex++;

		}

		counter++;
		Sleep(TIMER + 25);

	}

		Sleep(1000);

		setTextColor(Color::WHITE);
	
}

void printOpener()
{

	setTextColor(Color::LIGHTRED);

	gotoxy(65, 7);
	cout << " ||||";
	gotoxy(65, 7 + 1);
	cout << "||   ";
	gotoxy(65, 7 + 2);
	cout << "  || ";
	gotoxy(65, 7 + 3);
	cout << "   ||";
	gotoxy(65, 7 + 4);
	cout << "|||| ";

	setTextColor(Color::LIGHTGREY);

	gotoxy(59, 7);
	cout << "|||||";
	gotoxy(59, 7 + 1);
	cout << "||   ";
	gotoxy(59, 7 + 2);
	cout << "|||||";
	gotoxy(59, 7 + 3);
	cout << "||   ";
	gotoxy(59, 7 + 4);
	cout << "|||||";



	setTextColor(Color::LIGHTGREY);

	gotoxy(52, 7);
	cout << "||  ||";
	gotoxy(52, 7 + 1);
	cout << "||||  ";
	gotoxy(52, 7 + 2);
	cout << "||||  ";
	gotoxy(52, 7 + 3);
	cout << "|| || ";
	gotoxy(52, 7 + 4);
	cout << "||  ||";


	setTextColor(Color::LIGHTGREY);

	gotoxy(42, 7);
	cout << "    ||   ";
	gotoxy(42, 7 + 1);
	cout << "   ||||  ";
	gotoxy(42, 7 + 2);
	cout << "   |  |  ";
	gotoxy(42, 7 + 3);
	cout << "  |||||| ";
	gotoxy(42, 7 + 4);
	cout << " ||    ||";


	setTextColor(Color::LIGHTGREY);


	gotoxy(35, 7);
	cout << "||   ||";
	gotoxy(35, 7 + 1);
	cout << "|||  ||";
	gotoxy(35, 7 + 2);
	cout << "|| | ||";
	gotoxy(35, 7 + 3);
	cout << "||  |||";
	gotoxy(35, 7 + 4);
	cout << "||   ||";


	setTextColor(Color::LIGHTRED);


	gotoxy(29, 7);
	cout << " ||||";
	gotoxy(29, 7 + 1);
	cout << "||   ";
	gotoxy(29, 7 + 2);
	cout << "  || ";
	gotoxy(29, 7 + 3);
	cout << "   ||";
	gotoxy(29, 7 + 4);
	cout << "|||| ";


	setTextColor(Color::LIGHTGREY);

	gotoxy(21, 7);
	cout << "|||||";
	gotoxy(21, 7 + 1);
	cout << "||   ";
	gotoxy(21, 7 + 2);
	cout << "|||||";
	gotoxy(21, 7 + 3);
	cout << "||   ";
	gotoxy(21, 7 + 4);
	cout << "|||||";


	setTextColor(Color::LIGHTGREY);


	gotoxy(14, 7);
	cout << "||  ||";
	gotoxy(14, 7 + 1);
	cout << "||  ||";
	gotoxy(14, 7 + 2);
	cout << "||||||";
	gotoxy(14, 7 + 3);
	cout << "||  ||";
	gotoxy(14, 7 + 4);
	cout << "||  ||";



	setTextColor(Color::LIGHTGREY);


	gotoxy(7, 7);
	cout << "||||||";
	gotoxy(7, 7 + 1);
	cout << "  ||  ";
	gotoxy(7, 7 + 2);
	cout << "  ||  ";
	gotoxy(7, 7 + 3);
	cout << "  ||  ";
	gotoxy(7, 7 + 4);
	cout << "  ||  ";


	setTextColor(Color::LIGHTMAGENTA);

	gotoxy(24, 15);
	cout << "||||||    ||    ||||  |||| |||||";
	gotoxy(24, 15 + 1);
	cout << "||       ||||   ||  ||  || ||   ";
	gotoxy(24, 15 + 2);
	cout << "|| ||||  |  |   ||  ||  || |||||";
	gotoxy(24, 15 + 3);
	cout << "||  ||  ||||||  ||  ||  || ||   ";
	gotoxy(24, 15 + 4);
	cout << "|||||| ||    || ||      || |||||";

	setTextColor(Color::WHITE);

}