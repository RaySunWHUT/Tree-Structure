#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Header.h"

#pragma warning(disable:4996)


int CountLength(Hpointer* Array) {    /* 统计权值非零的结点的个数 */

	int cnt = 0;

	for (int j = 0; j < 60; j++) {

		if (Array[j]->Weight != 0) {

			cnt++;

		}

	}

	return cnt;

}



void PrintSToW(Hpointer* Array, int ArrayLength) {    /* 输出字符对应权值 */

	int j;
	/* 统计各字符的权值 */
	printf("symbol  weight\n");

	for (j = 0; j < ArrayLength; j++) {

		printf("%3c  %6d\n", Array[j]->Symbol, Array[j]->Weight);

	}

}


Hpointer* Filter(Hpointer* Array, int ArrayLength) {    /* 筛选权值非零的结点, Array为要筛选的结点 */

	int j;
	int i = 0;
	int cnt = CountLength(Array);

	Hpointer* ArrayNoZero = (Hpointer*)malloc(HPSIZE * cnt);

	for (j = 0; j < ArrayLength; j++) {

		if (Array[j]->Weight != 0) {

			ArrayNoZero[i++] = CreateHuffmanNode(Array[j]->Symbol, Array[j]->Weight);

		}

	}

	return ArrayNoZero;

}


void InorderTraversal(Hpointer Root) {   /* 调试时，辅助使用 */

	if (Root != NULL) {

		InorderTraversal(Root->Left);
		printf("%4d", Root->Weight);
		InorderTraversal(Root->Right);

	}

}


Hpointer* ArrayReverse(Hpointer* Array, int ArrayLength) {   /* 将数组元素中的元素逆转 */

	int Transform[MAXSIZE];  /* 中间装换容器 */
	int i = 0;
	int t = 0;
	int j = 0;
	for (i = 0; i < ArrayLength; i++) {   /* 将Array存放的指针指向的字符的编码转置，从而得到从根到叶的编码 */

		for (t = 0; Array[i]->Bytes[t] != -1; t++) {

			Transform[t] = Array[i]->Bytes[t];

		}

		t--;    /* 移动到hello[t]数组的有效下标的最后一位 */

		for (j = 0; t >= 0; t--, j++) {

			Array[i]->Bytes[j] = Transform[t];

		}

		Array[i]->Bytes[j] = -1;   /* -1标记结束 */

	}

	return Array;

}





