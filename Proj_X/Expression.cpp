#include "Expression.h"

Tree* tree = new Tree;;


bool Expression::buildExpressionTree(char str[])
{
	Tree* temp;								 // New tree will be pointerd to here

	temp = buildExpressionTreeHelper(str);	 // Get the tree

	if (temp == nullptr)						 // Info on the string is invalid	
	{
		tree->root = nullptr;
		return false;
	}
	else
	{
		tree->root = temp->root;				 // Tree has been built -> point root to tree's root
		return true;
	}
}

Tree* Expression::buildExpressionTreeHelper(char str[])
{

	Tree* res, *left, *right;									// res = current tree // left = left subtree // right = right subtree
	TreeNode* root;												// Current tree's root
	int index, len;												// Index = root index // len = string length
	char* strR, *strL;											// strR = right substring // strL = left substring

	len = strlen(str);											// Get string length

	if (len == 0)												// Invalid info
		return nullptr;
	if (len <= 3)												// Base case
	{
		int currLen;
		if (isOperand(str, currLen))
		{
			char * data = new char[currLen + 1];
			int i=0;
			for (i = 0; i < currLen; i++)
				data[i] = str[i];

			data[i] = '\0';
			root = createNewTnode(data, nullptr, nullptr);
		}
		
		
		else
			return nullptr;											// Invalid info
	}

	else
	{
		index = getRootIndex(str);									// Get root index					
		if (index == ERROR)												// Invalid info
			return nullptr;
		else                                                            // Info is valid
		{
			strL = createStrHelper(str, 0, index);							// Get left substring
			strR = createStrHelper(str, index, len - 1);						// Get right substring

			left = buildExpressionTreeHelper(strL);							// Get left subtree
			right = buildExpressionTreeHelper(strR);						// Get right subtree

			free(strL);														// Free substrings from memory
			free(strR);

			if (left == nullptr || right == nullptr)								// One or both of the subtrees are not legit
				return nullptr;
			else
			{
				char* Oper = new char[2];
				Oper[0] = str[index];
				Oper[1] = '\0';

				root = createNewTnode(Oper, left->root, right->root);		// Subtrees are legit -> create a new root with the above subtrees as children
			}
				
		}
	}

	res = (Tree*)malloc(sizeof(Tree));										// Allocate new memory for the tree
	res->root = root;														// Set tree's root
	return res;																// Return tree
}



TreeNode* Expression::createNewTnode(char* data, TreeNode* left, TreeNode* right)
{
	TreeNode* res;											// The new Tree Node
	res = (TreeNode*)malloc(sizeof(TreeNode));				// Allocate memory
	res->data = data;										// Enter data into new Tree Node
	res->left = left;										// Set left subtree
	res->right = right;										// Set right subtree
	return res;
}


void Expression::freeTree(Tree tr)
{
	freeTreeHelper(tr.root);
}

void Expression::freeTreeHelper(TreeNode* root)
{
	if (root == nullptr)										// Base case: Empty tree
		return;
	else
	{
		if (root->left == nullptr && root->right == nullptr)		// Recursive call 1: root is a leaf
			free(root);
		else
		{
			if (root->left != nullptr)							// Recursive call 2: root has a left child
				freeTreeHelper(root->left);
			if (root->right != nullptr)						// Recursive call 3: root has a right child
				freeTreeHelper(root->right);
			free(root);
		}

	}
}

bool Expression::isOperator(char ch)
{
	switch (ch)								// Check if the char is one of the valid operators
	{
	case '+':
		return true;
	case '-':
		return true;
	case '*':
		return true;
	case '/':
		return true;
	case '%':
		return true;
	default:
		return false;
	}
}


int Expression::getRootIndex(char str[])
{
	Operator* opArr, minPars, max;												// opArr = type Operator array to hold info about each operator
																				// minPars = will hold the index of the root // max = max left '(' and right ')' parentheses
	int i, write = 0, leftPars = 0, rightPars = 0, len = strlen(str), opCount = 0;		// i = index // write = write index for opArr // leftPars = counts '(' // rightPars = counts ')'
																						// len = strinf length // opCount = counts operators
	if (str == nullptr)
		return ERROR;																// Invalid info

	for (i = 0; i < len; i++)													// Count '('s, ')'s and operators
	{
		if (str[i] == '(')
			leftPars++;
		if (str[i] == ')')
			rightPars++;
		if (isOperator(str[i]) == true)
			opCount++;
	}

	if (leftPars != rightPars)													// Check validity
		return ERROR;
	if (opCount != (leftPars + rightPars) / 2)
		return ERROR;

	max.leftPars = leftPars;													// Save max '(' and ')' values
	max.rightPars = rightPars;

	leftPars = rightPars = 0;													// Reset leftPars and rightPars

	opArr = (Operator*)malloc(opCount * sizeof(Operator));						// Create an opArr the size of the number of operators found

	for (i = 0; i < len; i++)
	{
		if (str[i] == '(')														// Count '('s and ')'s
			leftPars++;
		if (str[i] == ')')
			rightPars++;

if (isOperator(str[i]) == true)											// If an operator is reached
{
	opArr[write].index = i;													// Enter info into opArr
	opArr[write].leftPars = leftPars;
	opArr[write].rightPars = max.rightPars - rightPars;

	if (write == 0)														// If it is the first operator enter its info into minPars
		minPars = opArr[write];
	else                                                                // Not first operator -> enter into minPars only if has the least '('s / ')'s to its left/right
		if (opArr[write].leftPars + opArr[write].rightPars < minPars.leftPars + minPars.rightPars)
			minPars = opArr[write];

	write++;															// Advance write index

}
	}

	free(opArr);																// Free opArr from memory
	return minPars.index;														// Return the root's index
}

char* Expression::createStrHelper(char str[], int leftLim, int rightLim)
{
	int i, write = 0, len = rightLim - leftLim - 1;								// i = index // write = write index for the new string // len = the needed length
	char* res = (char*)malloc((len * sizeof(char)) + 1);							// res = the new string

	for (i = leftLim + 1; i < rightLim; i++, write++)							// Copy the requested section of the parent string into the substring
		res[write] = str[i];

	res[write] = '\0';															// Set end of substring

	return res;																	// Return substring
}

int Expression::calcExpression(Tree tr)
{
	return calcExpressionHelper(tr.root);
}

int Expression::calcExpressionHelper(TreeNode* root)
{
	int res, left, right;													// res = expression's result // left = left sub-expression // right = right sub-expression
	int dummy;

	if (isOperand(root->data, dummy))									// Base case: If root contains and operand return it as the result
		return (atoi(root->data));
	else
	{
		left = calcExpressionHelper(root->left);								// Recursive call: If root contains an arithmetic expression calculate it
		right = calcExpressionHelper(root->right);
		res = calcByOperator(left, *(root->data), right);

		return res;																// Return result
	}
}

int Expression::calcByOperator(int left, char _operator, int right)
{
	switch (_operator)															// Calculate expression according to the given operator
	{
	case '+':
		return left + right;
		break;
	case '-':
		return left - right;
		break;
	case '*':
		return left * right;
		break;
	case '/':
		return left / right;
		break;
	case '%':
		return left % right;
		break;
	}
}


int Expression::calculate(char* expression)
{
	int res = -999;

	bool flag = buildExpressionTree(expression);

	if (flag) res = calcExpression(*tree);

	if (tree->root != nullptr) freeTree(*tree);
	tree->root = nullptr;

	return res;


}

bool Expression::isOperand(char* strStart, int& len)
{
	len = 0;

	if (strStart[0] - '0' >= 0 && strStart[0] - '0' <= 9)
	{
		while (strStart[len] - '0' >= 0 && strStart[len] - '0' <= 9)
			len++;

		return true;


	}

	return false;
		

}