#pragma once

#define ESIZE sizeof(ElementType)
#define SSIZE sizeof(struct Stack)

#define MAXSIZE 20   /* 字符编码0、1序列的长度 */

#define MINDATA -1000  /* 最小堆Data[0]位置的元素 */

#define HPSIZE sizeof(struct Huffman*)

#define HSIZE sizeof(struct Huffman)

#define MSIZE sizeof(struct MinHeap)  

#define ISIZE sizeof(int)

#define INFINITY 1000

#define END '#'

typedef int ElementType;
typedef int bool;

typedef enum Status {    /* 利用枚举(enum)制造boolean数据类型 */

	False = 0,
	True

} Status;


typedef struct Huffman {  /* 定义哈夫曼树的结构，带多重权值的三叉链表 */

	char Symbol;
	ElementType Weight;
	int Bytes[MAXSIZE];     /* 存储对应字符的0、1二进制编码序列 ; 以 -1 作为编码的结尾, 标记哨兵  */
	struct Huffman* Parent;   /* 父结点 */
	struct Huffman* Left;
	struct Huffman* Right;

} HuffmanTree, *Hpointer;



typedef struct Stack {      //利用堆栈实现：非递归遍历

	Hpointer TreeNode;
	struct Stack* Next;

} Stack, *Spointer;


bool IsSEmpty(Spointer headp);    /* 堆栈相关操作 */
Spointer CreateStack();
Spointer Push(Spointer headp, Hpointer TreeNode);
Hpointer Pop(Spointer headp);



typedef struct MinHeap {   /* 最小堆 */

	Hpointer* Data;    /* 数据 , 数组 */
	int Capacity;     /* 容量 */
	int Size;    /* 当前元素个数 */

} MinHeap, *MinHpointer;


MinHpointer CreateMinHeap(int MaxSize);  /* 与MinHeap有关的函数，均为构建哈夫曼树的过程函数 */
bool IsFull(MinHpointer MinH);
bool Insert(MinHpointer MinH, Hpointer X);
bool InsertIDo(MinHpointer MinH, Hpointer X);
bool IsEmpty(MinHpointer MinH);
Hpointer DeleteMin(MinHpointer MinH);
void PercDownIDo(MinHpointer MinH, int p);
void BulidHeap(MinHpointer MinH);



void Output(MinHpointer MinH);         /* 调试时使用 */
void InorderTraversal(Hpointer Root);     /* 调试时使用 */



Hpointer* ReadFile();        /* 创建哈夫曼树的基本流程 */
Hpointer* Filter(Hpointer* Array, int ArrayLength);
Hpointer CreateHuffmanTree(MinHpointer MinH);  
Hpointer* GetLeaves(Hpointer Root, int LeavesNumber);    
Hpointer* GetBytesWay(Hpointer* Leaves, int cnt);   
Hpointer* ArrayReverse(Hpointer* Array, int ArrayLength); 
void PrintBytes(Hpointer* Goal, int cnt);
void WriteFile(Hpointer Array[], int ArrayLength);      /* 将字符写入文件，结束！ */



Hpointer CreateHuffmanNode(char symbol, int weight);    /* 过程函数 */
void PrintSToW(Hpointer* Array, int ArrayLength);   
int CountLength(Hpointer* Array);  
