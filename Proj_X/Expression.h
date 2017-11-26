#ifndef _EXPRESSION_
#define _EXPRESSION_

//#define SIZE 100
#define ERROR -1

#include "ExpTree.h"
#include <string>
#include <iostream>

class Expression {

private:


	bool isOperator(char ch);
	bool isOperand(char* strStart, int& len);
	bool buildExpressionTree(char str[]);
	Tree* buildExpressionTreeHelper(char str[]);
	int calcExpression(Tree tr);
	int calcExpressionHelper(TreeNode* root);
	int calcByOperator(int left, char _operator, int right);
	int getRootIndex(char str[]);
	char* createStrHelper(char str[], int leftLim, int rightLim);
	
	void freeTree(Tree tr);
	void freeTreeHelper(TreeNode* root);


public:

	int calculate(char* expression);
	TreeNode* createNewTnode(char* data, TreeNode* left, TreeNode* right);






};

#endif