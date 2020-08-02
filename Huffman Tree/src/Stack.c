#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Header.h"

#pragma warning(disable:4996)


Spointer CreateStack() {     //堆栈实现非递归

	Spointer headp;

	headp = (Spointer)malloc(SSIZE);
	headp->Next = NULL;

	return headp;

}


Spointer Push(Spointer headp, Hpointer TreeNode) {   // 入栈

	Spointer p, firstp;

	firstp = headp->Next;
	p = (Spointer)malloc(SSIZE);

	headp->Next = p;
	p->TreeNode = TreeNode;

	if (IsSEmpty(headp)) {

		p->Next = NULL;

	}
	else {

		p->Next = firstp;    // 关键操作 

	}

	return headp;

}


Hpointer Pop(Spointer headp) {    // 出栈

	Spointer p = headp->Next;
	Hpointer tree = NULL;

	if (IsSEmpty(headp)) {

		printf("It's a empty Stack!\n");

	}
	else {

		headp->Next = p->Next;
		tree = p->TreeNode;
		free(p);

	}

	return tree;

}


bool IsSEmpty(Spointer headp) {    // 判空 

	return (headp->Next == NULL);

}
