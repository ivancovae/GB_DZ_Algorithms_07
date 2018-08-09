typedef unsigned int u_int;

// тип указателя на ноду
typedef struct tagNode * pNode;

// тип ноды
typedef struct tagNode
{
	u_int weight;
	pNode next;
} Node;

// тип структуры листа
typedef struct tagList
{
	pNode head;
	int size;
	int maxSize;
} List;

typedef List * pList;


typedef u_int bool;
#define true 1
#define false 0

// тип указателя на ноду
typedef struct tagQueueNode * pQueueNode;

// тип ноды
typedef struct tagQueueNode
{
	int num;
	pQueueNode next;
} QueueNode;

// тип структуры очередь
typedef struct tagQueue
{
	pQueueNode front;
	pQueueNode back;
	int size;
	int maxSize;
} Queue;

typedef Queue * pQueue;

// тип структуры стека
typedef struct tagStack
{
	pQueueNode head;
	int size;
	int maxSize;
} Stack;

typedef Stack * pStack;

int **readMatrixFromFile(char *filename, int *V, int *E);
void printGraph(int **graph, int vertexs);
void freeGraph(int **graph, int vertexs);

void initQueue(pQueue queue);
void initStack(pStack stack);

void BFS(pQueue queue, pQueue queueUsed, int numNode, int **graph, int vertexs);
void DFS(pStack stack, pQueue queueUsed, int numNode, int **graph, int vertexs);