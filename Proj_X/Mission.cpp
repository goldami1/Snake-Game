#include "Mission.h"

Expression expression;


bool Mission::true_equation()
{

	int x1, x2, x3, z, solution, res, leftExpRes = 0;
	char op1, op2;
	bool leftExpFirst = false;

	x1 = equation[0];
	op1 = equation[1];
	x2 = equation[2];
	op2 = equation[3];
	x3 = equation[4];
	solution = equation[5];

	if ((op1 == DIV && x2 == 0) || (op2 == DIV && x3 == 0))
		return false;

	if (op1 == MULT || op1 == DIV)
	{
		leftExpFirst = true;
		if (op1 == MULT) leftExpRes = x1*x2;
		else leftExpRes = x1 / x2;
	}

	if (leftExpFirst) z = leftExpRes;
	else z = x2;

	if (op2 == MULT) res = z * x3;
	if (op2 == DIV) res = z / x3;
	if (op2 == PLUS) res = z + x3;
	if (op2 == MINUS) res = z - x3;

	if (!leftExpFirst)
	{
		if (op1 == PLUS) res = x1 + res;
		else res = x1 - res;
	}

	if (res == solution) return true;
	else return false;

}

bool Mission::init()
{
	//	static char i = MISSION_INITALIZER;
	//	if (i >= MISSIONS_FULLY_INITIALIZED)
	//	{
	//		system("cls");
	//		cout << "There was an error in initializing the missions. Please check Mission class or its dependencies." << endl;
	//		exit(1);
	//	}
	//	nameRef = i;
	//	i++;
	return true;
}

void Mission::printMission()
{
	gotoxy(1, 1);
	setTextColor(WHITEONBLUE);
	cout << "Mission: ";
	cout << currText;

	if (equation_flag) print_equation();

}

bool Mission::succeed(int valueOfNumber)
{
	bool res = false;
	int result = -999;

	char sol[40];

	if (equation_flag)
	{
		insertNumToEq(valueOfNumber);
		char res = true_equation();
		return res;

	}
	else if (loop)
	{
		for (loop_index = 0; loop_index < valueOfNumber; loop_index++)
		{
			if ((notZero) || loop_index > 0)
			{
				insertParameters(sol, condition, valueOfNumber);
				result = expression.calculate(sol);
				if (result == _Solution) return loop_cond_res;
			}
	

		}

		return !loop_cond_res;

	}
	else
	{
		insertParameters(sol, condition, valueOfNumber);
		result = expression.calculate(sol);

		if (result != -999)
			if (result == _Solution)
				return true;

	}
	


	return false;
}


void Mission::randomize_equation()
{
#define OPERAND_1 0
#define OPERAND_2 2
#define OPERAND_3 4
#define OPERATOR_1 1
#define OPERATOR_2 3
#define SOLUTION 5

	int blank_index, op_ref, x1, x2, x3, solution = 0, op1, op2, operators[] = { PLUS, MINUS, MULT, DIV };
	bool ignore = false;

	blank_index = rand() % 4;
	op_ref = rand() % 4;
	op1 = operators[op_ref];
	op_ref = rand() % 4;
	op2 = operators[op_ref];

	if (blank_index == 1) { blank_index = OPERAND_2; }
	else if (blank_index == 2) { blank_index = OPERAND_3; }
	else if (blank_index == 3) blank_index = SOLUTION;

	x2 = rand() % 20 + 1;
	x3 = (rand() % 15 + 1);
	x1 = (rand() % 30 + 1);

	if (op1 == MULT)														// Perform a series of comparisons to make the equation more likely to have a solution on the board
	{
		if (x1 > x2) x2 = rand() % 11 + 4;
		else x1 = rand() % 8 + 4;
	}
	if (op1 == MINUS)
		if (x1 < x2) {
			x2 += (rand() % 11 + 10); x1 += x2*(rand() % 10 + 2);
		}
	if (op1 == DIV) x1 = x2* ((rand() % 12) + 4);
	if (op2 == MULT)
	{
		if (x3 > x2) x3 = (rand() % 12 + 2);
		else x2 = rand() % 9 + 2;
	}
	if (op2 == MINUS || op1 == DIV || op1 == MINUS || op2 == DIV) x3 = rand() % 12 + 2;
	if (op1 == PLUS)
	{
		if (op2 != MULT && op2 != DIV) solution = x1 + x2;
		else
		{
			ignore = true;
			if (op2 == MULT) solution = x1 + x2*x3;
			if (op2 == DIV) solution = x1 + x2 / x3;
		}
	}
	if (op1 == MINUS)
	{
		if (op2 != MULT && op2 != DIV) solution = x1 - x2;
		else
		{
			ignore = true;
			if (op2 == MULT)
			{
				x1 *= (rand() % 5 + 2);
				solution = x1 - x2*x3;
			}
			if (op2 == DIV) solution = x1 - x2 / x3;
		}
	}
	if (!ignore)
	{
		if (op1 == DIV) solution = x1 / x2;
		if (op1 == MULT) solution = x1*x2;
		if (op1 == PLUS) solution = x1 + x2;
		if (op1 == MINUS) solution = x1 - x2;
		if (op2 == DIV) solution /= x3;
		if (op2 == MULT) solution *= x3;
		if (op2 == PLUS) solution += x3;
		if (op2 == MINUS) solution -= x3;
	}
	equation[OPERAND_1] = x1;
	equation[OPERAND_2] = x2;
	equation[OPERAND_3] = x3;
	equation[SOLUTION] = solution;
	equation[OPERATOR_1] = op1;
	equation[OPERATOR_2] = op2;
	equation[blank_index] = BLANK;
	blank_eq_index = blank_index;



	for (int i = 0; i < SOLUTION; i++)
		if (equation[i] == BLANK && i != blank_index)
			equation[i] = 1;
}

void Mission::print_equation()
{
	bool blank = false;
	gotoxy(39, 1);
	setTextColor(Color::WHITEONBLUE);
	for (int i = 0; i < 6; i++)
	{
		if (equation[i] == BLANK)
		{
			if (!blank)
			{
				cout << "_____ ";
				blank = true;
			}
			else
			{
				equation[i] = (rand() % 12 + 1);
				cout << equation[i] << " ";
			}
		}
		else if (i == 0 || i == 2 || i == 4 || i == 5)
			cout << equation[i] << " ";
		else
		{
			if (equation[i] == PLUS) cout << "+ ";
			if (equation[i] == MINUS) cout << "- ";
			if (equation[i] == MULT) cout << "X ";
			if (equation[i] == DIV) cout << ": ";
		}
		if (i == 4) cout << "= ";
	}
}

void Mission::insertNumToEq(int num)
{
	equation[blank_eq_index] = num;
		
}

void Mission::breakIntoSections(const char* description)
{
	// Asumption: all sections in the input string are of valid size
	
	char* _text, *_random_part, *_condition;
	int section=1;
	int text_ind=0, rand_ind=0, cond_ind = 0;

	_text = new char[60];
	_random_part = new char[30];
	_condition = new char[30];

	for (int i = 0; i < MAXCHARSONSTRING && description[i] != '\0'; i++)
	{

		if (description[i] == '$')
			section++;
		else
		{
			switch (section)
			{

			case 1:											// free text section
				text[text_ind] = description[i];
				text_ind++;
				break;

			case 2:											// random part
				random_part[rand_ind] = description[i];
				rand_ind++;
				break;

			case 3:											// how to find the correct solution
				if (description[i] == 'L')
					loop = true;
				else if (description[i] == 'T')
					loop_cond_res = true;
				else if (description[i] == 'F')
					loop_cond_res = false;
				else if (description[i] == 'E')
				{
					blank_eq_index = 0;
					randomize_equation();
					equation_flag = true;
				}
				
				else
				{
					condition[cond_ind] = description[i];
					if (description[i] == '/' || description[i] == '%')
						notZero = false;
					cond_ind++;
					break;

				}
				

			}

		}
	
	}


	text[text_ind] = '\0';
	random_part[rand_ind] = '\0';
	condition[cond_ind] = '\0';



}

void Mission::setMission(char* description)
{
	breakIntoSections(description);
	randomize();
	setTextForCurrentMission();

}

void Mission::randomize()
{
	int index = 0;
	int varInd = 0;

	while (random_part[index] != '\0')
	{
		if (isVar(random_part[index]))
		{
			int left_limit, right_limit, temp_ind=0;

			char* temp = new char[4];
			index++;

			while (random_part[index] -'0' >= 0 && random_part[index] -'0' <= 9)
			{
				temp[temp_ind] = random_part[index];
				temp_ind++;
				index++;

			}
			temp[temp_ind] = '\0';
			index++;

			left_limit = atoi(temp);
			temp_ind = 0;

			while (random_part[index] -'0' >= 0  && random_part[index] -'0' <= 9)
			{
				temp[temp_ind] = random_part[index];
				temp_ind++;
				index++;

			}

			temp[temp_ind] = '\0';
			index++;

			right_limit = atoi(temp);

			delete temp;

			vars[varInd] = rand() % (right_limit - left_limit) + left_limit;
			varInd++;

		//	index += 3;

		}
		else index++;

	}

	while (varInd < 5)
		vars[varInd++] = BLANK;
	
		
	
}

void Mission::setTextForCurrentMission()
{
	int varInd = 0, currTextInd = 0;

	for (int i = 0; i < strlen(text); i++)
	{
		if (text[i] != '&')
			currText[currTextInd] = text[i];
			
		else
		{
			if (vars[varInd] == BLANK)
			{
				currText[currTextInd] = '\0';
				return;
			}

			char* temp = intToString(vars[varInd]);
			int temp_ind = 0;
			while (temp_ind < strlen(temp))
				currText[currTextInd++] = temp[temp_ind++];

			delete temp;
			i++;
			varInd++;

			currTextInd  --;
		}
		currTextInd++;
			
	}

	currText[currTextInd] = '\0';

	
}

void Mission::insertParameters(char* dest, char* src, int n)
{
	int varIndex = 0;
	int i, write=0;


	for (i = 0; i < strlen(src) && src[i] != '='; i++)
	{
		if (isVar(src[i]))
		{
			if (src[i] == 'n')
			{
				char* num = intToString(n);
				for (int j = 0; j < strlen(num); j++)
					dest[write++] = num[j];
				delete num;

			}
			else if (src[i] == 'i')
			{
				char* num = intToString(loop_index);
				for (int j = 0; j < strlen(num); j++)
					dest[write++] = num[j];
				delete num;

			}
			else
			{
				char* num = intToString(getVarValue(src[i]));
				for (int j = 0; j < strlen(num); j++)
					dest[write++] = num[j];
				delete num;
			}
				
		}
		else
			dest[write++] = src[i];
	}

	dest[write] = '\0';

	i++;

	if (src[i] == 'n')
		_Solution = n;
	else if (isVar(src[i])) _Solution = getVarValue(src[i]);
	else _Solution = src[i] - '0';

}

int Mission::getVarValue(char var)
{
	switch (var)
	{
	case 'a':
		return vars[A];
		break;

	case 'b':
		return vars[B];
		break;

	case 'c':
		return vars[C];
		break;

	case 'd':
		return vars[D];
		break;

	case 'e':
		return vars[E];
		break;
	case 'i':
		return vars[LOOP_INDEX];
		break;

	default:
		return ERROR;
		break;


	}


}

char* Mission::intToString(int num)
{
	char* res;
	int temp = num, len = 0;

	if (num == 0)
	{
		res = new char[2];
		res[0] = '0';
		res[1] = '\0';
	}
	else
	{
		while (temp > 0)
		{
			len++;
			temp /= 10;

		}

		res = new char[len + 1];
		for (int i = len - 1; i >= 0; i--)
		{
			res[i] = num % 10 + '0';
			num /= 10;
		}

		res[len] = '\0';
	}
	


	return res;



}