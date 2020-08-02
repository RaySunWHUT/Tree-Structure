#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Header.h"

#pragma warning(disable:4996)


MinHpointer CreateMinHeap(int MaxSize) {   /* 创建最小堆 */

	MinHpointer MinHeap = (MinHpointer)malloc(MSIZE);

	Hpointer Top = (Hpointer)malloc(HSIZE);    /* 初始化哨兵结点 */

	Top->Symbol = -1;
	Top->Weight = MINDATA;
	Top->Left = Top->Right = NULL;
	Top->Parent = NULL;

	MinHeap->Data = (Hpointer *)malloc((MaxSize + 1) * HPSIZE);   /* HPSIZE 为struct Huffman*的大小 */
	MinHeap->Capacity = MaxSize;
	MinHeap->Size = 0;
	MinHeap->Data[0] = Top;   /* 哨兵结点 */

	return MinHeap;

}


int GetHeight(Hpointer Tree) {     // 求树高 

	int LH, RH, MaxH;

	if (Tree != NULL) {

		LH = GetHeight(Tree->Left);
		RH = GetHeight(Tree->Right);
		MaxH = LH > RH ? LH : RH;

		return MaxH + 1;

	}
	else {

		return 0;   // 空树

	}

}


bool IsFull(MinHpointer MinH) {     /* 判满 */

	return (MinH->Size == MinH->Capacity);

}


bool Insert(MinHpointer MinH, Hpointer X) {

	int i;   /* 即插入结点后堆中最后一个结点的位置 */

	if (IsFull(MinH)) {

		printf("最大堆已满\n");

		return False;

	}
	else {

		i = ++MinH->Size;

		for (; X->Weight < MinH->Data[i / 2]->Weight; i = i / 2) {

			MinH->Data[i] = MinH->Data[i / 2];

		}

		MinH->Data[i] = X;

		return True;

	}

}


bool InsertIDo(MinHpointer MinH, Hpointer X) {   /* I do. */

	Hpointer Temp;
	int End = MinH->Size + 1;   /* 即插入结点后堆中最后一个结点的位置 */

	if (IsFull(MinH)) {

		printf("最大堆已满\n");

		return False;

	}
	else {

		if (X->Weight > MinH->Data[MinH->Size++]->Weight) {   /* 勿忘记增大最大堆的元素个数 */

			MinH->Data[End] = X;

		}
		else {

			for (int i = End / 2; X->Weight < MinH->Data[i]->Weight; i = i / 2) {

				Temp = MinH->Data[i];
				MinH->Data[i] = X;
				MinH->Data[End] = Temp;
				End = i;

			}

		}

		return True;

	}

}


bool IsEmpty(MinHpointer MinH) {

	return (MinH->Size == 0);

}


Hpointer DeleteMin(MinHpointer MinH) {

	int Parent, Child;
	Hpointer MinItem, X;

	if (IsEmpty(MinH)) {  /* 空堆 */

		printf("最大堆为空\n");
		return NULL;

	}

	MinItem = MinH->Data[1];    /* 取出根结点，最小元素 */
	X = MinH->Data[MinH->Size--];     /* 取出最后一个元素 */

	for (Parent = 1; Parent * 2 <= MinH->Size; Parent = Child) {

		Child = Parent * 2;
		if ((Child != MinH->Size) && (MinH->Data[Child]->Weight > MinH->Data[Child + 1]->Weight)) {   /* 未到达最后位置且左孩子大于右孩子 */

			Child++;    /* Child指向左右结点中的较小值 */

		}

		if (X->Weight <= MinH->Data[Child]->Weight) {

			break;

		}
		else {    /* X > MaxH->Data[Child] */

			MinH->Data[Parent] = MinH->Data[Child];

		}

	}

	MinH->Data[Parent] = X;

	return MinItem;

}


void PercDownIDo(MinHpointer MinH, int p) {     /* I do. */

	int i;
	bool Judge;
	Hpointer Temp;

	for (i = p; i * 2 < MinH->Size; i *= 2) {

		/* 根结点值小于左右子树中的值 */

		if (MinH->Size % 2 == 0 && p == MinH->Size / 2) {   /* 元素个数为偶数，则最后一个结点的父结点，只有一个孩子；*/
																 /* 此操作只在第一次执行此函数且最后一个结点没有兄弟结点时进行 */
			if (i != MinH->Size && (MinH->Data[i]->Weight < MinH->Data[2 * i]->Weight)) {

				break;

			}
			else {    /* 左右子树二者中值存在大于根结点的值 */

				Temp = MinH->Data[i];
				MinH->Data[i] = MinH->Data[2 * i];
				MinH->Data[2 * i] = Temp;

			}

		}
		else {    /* 元素个数为奇数，则最后一个结点的父结点，有两个孩子, 一切照旧 */

			if (i != MinH->Size && (MinH->Data[i]->Weight < MinH->Data[2 * i]->Weight && MinH->Data[i]->Weight < MinH->Data[2 * i + 1]->Weight)) {

				break;

			}
			else {    /* 左右子树二者中值存在大于根结点的值 */

				Judge = MinH->Data[2 * i]->Weight < MinH->Data[2 * i + 1]->Weight ? True : False;  /* 判断 */

				if (Judge) {

					Temp = MinH->Data[i];
					MinH->Data[i] = MinH->Data[2 * i];
					MinH->Data[2 * i] = Temp;

				}
				else {

					Temp = MinH->Data[i];
					MinH->Data[i] = MinH->Data[2 * i + 1];
					MinH->Data[2 * i + 1] = Temp;

				}

			}

		}

	}

}


void BulidHeap(MinHpointer MinH) {    /* 堆的建立 */

	int i;

	for (i = MinH->Size / 2; i >= 1; i--) {

		PercDownIDo(MinH, i);     //  PercDownIDo(MaxH, i);

	}

}


void Output(MinHpointer MinH) {    /* 调试时使用 */

	int i;

	for (i = 1; i <= MinH->Size; i++) {

		printf("%4d", MinH->Data[i]->Weight);

	}

}

