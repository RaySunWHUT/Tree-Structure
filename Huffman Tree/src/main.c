#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Header.h"

#pragma warning(disable:4996)

int main() {

	int cnt = 0, i = 0;
	Hpointer* Array = NULL;
	Hpointer* ArrayNoZero = NULL;

	MinHpointer MinH = NULL;

	Hpointer Root = NULL;
	Hpointer* Leaves = NULL;
	Hpointer* Goal = NULL;

	Array = ReadFile();    /* 返回键值与权值对应的容器Array */
	cnt = CountLength(Array);
	ArrayNoZero = Filter(Array, 60);    /* 过滤掉非零结点 */
	PrintSToW(ArrayNoZero, cnt);   

	MinH = CreateMinHeap(cnt);

	for (i = 0; i < cnt; i++) {

		Insert(MinH, ArrayNoZero[i]);

	}

	/*
	
	printf("\n输出最小堆：(检验)\n");
	Output(MinH);  

	*/

	Root = CreateHuffmanTree(MinH);  

	/*

	printf("\n中序遍历检验:\n");
	InorderTraversal(Root);   

	*/

	Leaves = GetLeaves(Root, cnt);

	Goal = GetBytesWay(Leaves, cnt);

	Goal = ArrayReverse(Goal, cnt);

	PrintBytes(Goal, cnt);   /* 查看各字符的编码 */

	WriteFile(Goal, cnt);

	return 0;

}


