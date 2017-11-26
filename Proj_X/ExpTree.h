#ifndef _EXPTREE_
#define _EXPTREE_

typedef struct treeNode
{
	char* data;
	struct treeNode *left;
	struct treeNode *right;
}TreeNode;

typedef struct tree
{
	TreeNode *root;
}Tree;

typedef struct op
{
	int index;
	int leftPars;
	int rightPars;
}Operator;

#endif
