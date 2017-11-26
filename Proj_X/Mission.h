#ifndef _MISSION_H_
#define _MISSION_H_

#include <iostream>
#include "io_utils.h"
#include "Point.h"
#include "Expression.h"

#define		BLANK					-1
#define		PLUS					-2
#define		MINUS					-3
#define		MULT					-4
#define		DIV						-5
#define		MAXCHARSONSTRING		120
#define		A						0
#define		B						1
#define		C						2
#define		D						3
#define		E						4
#define	    LOOP_INDEX				5
#define	    LOOP_START				0
#define	    LOOP_END				1

using namespace std;

//enum { MISSION_INITALIZER = 'A', PRIME_NUMBER = 'A', DIV_BY_4, DIV_BY_7, SQR_OF_INT, MOD_7_EQUALS_3, SQAURE_OF_13, TRUE_EQUATION, MISSIONS_FULLY_INITIALIZED };

class Mission {

//	char nameRef=MISSION_INITALIZER;
//	bool prime_number(int num);
//	bool div_by_4(int num);
//	bool div_by_7(int num);
//	bool sqr_of_int(int num);
//	bool mod_7_equals_3(int num);
//	bool sqr_of_13(int num);
	int equation[6] = { 5, MULT, 16, MINUS, 10, BLANK };
	int blank_eq_index = 0;
	int _Solution = 0;
	bool loop = false;
	int loop_index = 0;
	bool loop_cond_res = false;
	bool notZero = true;
	bool equation_flag = false;

	int vars[5];						// random part tp be displayed to the players
	int internalVars[4];				// for internal use while checking for mission success

	char currText[80];
	char text[80];
	char random_part[40];
	char condition[40];

	void breakIntoSections(const char* description);
	void randomize();

	bool isVar(char c) { if ((c - 'a') >= 0 && (c - 'a') <= 25) return true; else return false; }
	void setTextForCurrentMission();


public:
	bool init();
	void printMission();
	bool succeed(int valueOfNumber);
	void randomize_equation();
	void print_equation();
	void insertNumToEq(int num);

	void setMission(char* description);
	void insertParameters(char* dest, char* src, int n);
	char* intToString(int num);
	int getVarValue(char var);
	bool true_equation();

	
};


#endif