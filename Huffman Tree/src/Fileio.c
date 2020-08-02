#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Header.h"

#pragma warning(disable:4996)


Hpointer* ReadFile() {   /* 读取文件，统计文件中可能出现的字符频率，并将字符与对应字符的出现频率捆绑到一起 */

	FILE* fp;
	int i, j;
	int value;
	char fileName[256];
	Hpointer* Array = (Hpointer*)malloc(HPSIZE * 60);

	int weight[60] = { 0 };
	char key[60] = {

		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
		'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
		'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ',', '.', '!', ':', '?', '"', ' ', '\n'

	};

	printf("请输入文件名：");

	scanf("%s", &fileName);

	fp = fopen(fileName, "r");  /* 以只读方式读取文件 */

	while ((value = fgetc(fp)) != EOF) {    /* 当文件未到末尾时，统计各对应字符的权值 (即频数) */

		for (i = 0; i < 60; i++) {

			if (value == key[i]) {  /* 统计各结点的权值 */

				weight[i]++;
				break;

			}

		}

	}

	for (j = 0; j < 60; j++) {   /* 此处的目的是要将键值与频率捆绑为一个整体 */

		Array[j] = CreateHuffmanNode(key[j], weight[j]);   /* Array所存储的元素类型是：指向编码结构类型的指针 */

	}

	return Array;  /* 将各个键值与频率对应上后，统一到Array容器中，返回. */

}


void WriteFile(Hpointer Array[], int ArrayLength) {   /* 输入0、1序列，将编译后的结果写入文件 */

	int a[INFINITY] = { -1 };
	char Container[INFINITY];
	FILE * fp;
	int i, m = 0, k = 0;
	int cnt = 0;
	int n = 0;
	int record = 0, store = 0;
	int h = 0;
	int* length = (int *)malloc(ArrayLength * ISIZE);
	char Symbol[100] = { '0' };
	char fileName[256];


	printf("请输入需要生成的文件名：");
	scanf("%s", &fileName);

	fp = fopen(fileName, "w");

	printf("请输入0、1序列以供解码：(输入范围应小于1000)\n");

	// fflush(fp);
	getchar();
	gets(Container);

	for (i = 0; Container[i] != '\0'; i++) {

		a[i] = Container[i] - '0';

	}

	a[i] = -1;

	for (int j = 0; j < ArrayLength; j++) {

		for (m = 0; Array[j]->Bytes[m] != -1; m++) {}    /* 统计每个结点的编码长度 */

		length[j] = m;

	}


	for (; a[n] != -1; k++) {

		record = n;    /* 记录开始遍历前a[n]的位置 */

		for (m = 0; Array[k]->Bytes[m] != -1; m++, n++) {   /* 遍历对应字符的编码 */

			if (a[n] == Array[k]->Bytes[m]) {

				cnt++;

			}
			else {     /* 在与对应编码表对照结束前，若有不同，直接跳出！ */

				cnt = 0;   /* 查找失败，计数器归零 */
				break;

			}

		}

		store = n;    /* 记录遍历后的位置 */

		if (cnt == length[k]) {    /* a[n]的部分数组元素与字符编码完全对照上，则找到对应编码的字符 */

			Symbol[h++] = Array[k]->Symbol;  /* 将对应字符存入到字符数组中 */
			n = store;   /* 从刚才停止位置继续遍历. */
			cnt = 0;     /* 查找成功, 计数器归零. */

		}
		else {   /* 未成功对照，返回原位置继续查找 */

			n = record;

		}

		if (k == ArrayLength - 1) {    /* 全部遍历Array一遍后，重新开始 */

			k = -1;    /* 关键操作！！！ 此时若将k赋为0，则再次开始循环的时候，k++后k变为了1. */

		}

	}

	Symbol[h++] = END;

	h = 0;

	while (Symbol[h] != END) {

		fputc(Symbol[h], fp);
		h++;

	}

	fclose(fp);

}




