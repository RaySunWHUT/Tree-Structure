#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Header.h"

#pragma warning(disable:4996)


Hpointer CreateHuffmanNode(char symbol, int weight) {    /* 将字符与权值捆绑并赋值 */

	Hpointer EnHeadp;

	EnHeadp = (Hpointer)malloc(HSIZE);

	EnHeadp->Symbol = symbol;
	EnHeadp->Weight = weight;
	EnHeadp->Parent = NULL;      /* 勿忘记指针的初始化！ */
	EnHeadp->Left = EnHeadp->Right = NULL;      /* 将左右指针赋为NULL. */

	return EnHeadp;

}


Hpointer CreateHuffmanTree(MinHpointer MinH) {      /* 返回构建成功后，哈夫曼树的根结点 */

	Hpointer firstp = NULL, secondp = NULL, unity = NULL, Root = NULL;

	while (MinH->Size > 1) {

		unity = (Hpointer)malloc(HSIZE);
		firstp = DeleteMin(MinH); 
		secondp = DeleteMin(MinH);

		  /* 此时未使用firstp->Left = firstp->Right = NULL;的原因是在将结点插入堆之时，已将左右指针初始化为NULL*/

		firstp->Parent = secondp->Parent = unity;
		unity->Weight = firstp->Weight + secondp->Weight;
		unity->Parent = NULL;
		unity->Left = firstp;
		unity->Right = secondp;

		Insert(MinH, unity);

	}

	Root = DeleteMin(MinH);   /* 返回哈夫曼树的根结点 */
	Root->Parent = NULL;

	return Root;

}


Hpointer* GetLeaves(Hpointer Root, int LeavesNumber) {    /* 非递归中序遍历返回叶结点的集合 */

	Spointer headp = NULL;
	Hpointer BT = NULL;

	int k = 0;

	headp = CreateStack();
	BT = Root;
	Hpointer* Leaves = (Hpointer*)malloc(LeavesNumber * HPSIZE);

	while (BT != NULL || !IsSEmpty(headp)) {

		while (BT != NULL) {

			Push(headp, BT);
			BT = BT->Left;

		}

		BT = Pop(headp);

		if (BT->Left == NULL && BT->Right == NULL) {    /* 找到叶结点，再进行以下操作 */

			Leaves[k++] = BT;

		}

		BT = BT->Right;   /* 存在右结点，并转向右结点 */

	}

	return Leaves;

}


Hpointer* GetBytesWay(Hpointer* Leaves, int cnt) {    /* 获取对应结点字符的0、1序列， */

	int i, j = 0;
	int y = 0;
	Hpointer Orderp = NULL;

	for (i = 0; i < cnt; i++) {

		Orderp = Leaves[i];

		while (Orderp->Parent != NULL) {

			if (Orderp->Parent->Left == Orderp) {

				
				Leaves[i]->Bytes[j++] = 0;

			}
			else {

				Leaves[i]->Bytes[j++] = 1;

			}

			Orderp = Orderp->Parent;   /* 向上遍历 */

		}

		Leaves[i]->Bytes[j++] = -1;

		j = 0;

	}

	return Leaves;


}


void PrintBytes(Hpointer* Goal, int cnt) {   /* 调试时使用 */

	printf("\n各字符的编码为：\n");
	for (int i = 0; i < cnt; i++) {

		printf("%3c   ", Goal[i]->Symbol);

		for (int lx = 0; Goal[i]->Bytes[lx] != -1; lx++) {

			printf("%d", Goal[i]->Bytes[lx]);

		}

		printf("\n");

	}

}
