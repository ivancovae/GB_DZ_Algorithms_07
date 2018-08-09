#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>

void solution00();
void solution01();
void solution02();
void solution03();
void menu();

// Задание выполнил Иванцов Александр Евгеньевич
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");
	int select = 0;

	do
	{
		menu();
		scanf("%i", &select);
		switch (select)
		{
		case 1:
			solution00();
			break;
		case 2:
			solution01();
			break;
		case 3:
			solution02();
			break;		
		case 4:
			solution02();
			break;
		case 0:
			printf("Программа закончила свое выполнение.\n");
			break;
		default:
			printf("Некорректный символ, введите значения из списка меню.\n");
		}
	} while (select != 0);
	system("pause");
	return 0;
}

void menu()
{
	printf("Меню выбора решения задания:\n\n");

	printf("1. Решение задачи 1\n");
	printf("2. Решение задачи 2\n");
	printf("3. Решение задачи 3\n");
	printf("4. Решение задачи 4\n");
	printf("0. Завершение выполнения программы\n");
}

void descriptionTask(char *task)
{
	printf("\n##########################################\n");
	printf("\nУсловие задачи:\n");
	printf(task);
}

void endTask()
{
	printf("\n##########################################\n\n");
}

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

int ** readMatrixFromFile(char *filename, int *V, int *E)
{
	FILE * file;
	if ((file = fopen(filename, "r")) == NULL)
	{
		puts("Не удалось открыть файл!\n");
		return NULL;
	}
	else
	{
		char data[SHRT_MAX];
		int _V = 0; // число вершин
		int _E = 0; // число ребер

		int **graph = NULL;
		int posY = 0;
		int i = 0;

		// Решение
		printf("Результат: \n");

		// чтение Матрицы смежности графа из файла
		// первый элемент количество вершин
		// со следующей строки построчно матрица смежности
		while (!feof(file))
		{
			if (fgets(data, SHRT_MAX - 2, file))
			{
				int posX = 0;
				if (_V == 0)
				{
					_V = atoi(data);
					graph = (int **)malloc(_V * sizeof(int *));
					for (i = 0; i < _V; i++)
						graph[i] = (int *)malloc(_V * sizeof(int));
					continue;
				}
				
				for (int i = 0; i < strlen(data); i++)
				{
					char elem[SHRT_MAX];
					int j = 0;
					while (data[i] != ' ' && data[i] != '\0')
					{
						elem[j++] = data[i++];
					}
					elem[j] = '\0';

					int value = atoi(elem);
					if (value > 0)
					{
						_E++;
					}
					graph[posY][posX] = value;
					posX++;
				}
				posY++;
			}
		}
		fclose(file);

		printf("\nГраф имеет %d вершин и %d ребер\n", _V, _E);
		*V = _V;
		*E = _E;
		return graph;
	}
}

void printGraph(int **graph, int vertexs)
{
	for (int i = 0; i < vertexs; i++)
	{
		printf("%4d вершина - ", i);
		for (int j = 0; j < vertexs; j++)
			printf("%d ", graph[i][j]);
		printf("\n");
	}
}

void freeGraph(int **graph, int vertexs)
{
	if (graph != NULL)
	{
		for (int i = vertexs - 1; i > 0; i--)
		{
			free(graph[i]);
			graph[i] = NULL;
		}
		// проблема с очисткой последнего элемента
		free(graph);
	}
}

// Задание 1: Написать функции, которые считывают матрицу смежности из файла и выводят ее на экран.
void solution00()
{
	descriptionTask("Написать функции, которые считывают матрицу смежности из файла и выводят ее на экран.\n");
	// Ввод данных
	char filename[SHRT_MAX];

	printf("\nВведите файл, из которого будут считаны данные: ");
	scanf("%s", filename);

	int V = 0; // число вершин
	int E = 0; // число ребер

	int **graph = readMatrixFromFile(filename, &V, &E);
	printGraph(graph, V);
	//freeGraph(graph, V);
	endTask();
}

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


// инициализация очереди
void initQueue(pQueue queue)
{
	queue->maxSize = 100;
	queue->size = 0;
	queue->front = NULL;
	queue->back = NULL;
}

// очистка очереди
void clearQueue(pQueue queue)
{
	pQueueNode current = queue->front;
	while (current)
	{
		queue->front = current->next;
		free(current);
		current = NULL;
		current = queue->front;
		queue->size--;
	}
}

// возврат значения первого элемента без удаления элемента
void Peek(pQueue queue, int *value)
{
	if (queue->size == 0)
	{
		printf("Очередь пуста, необходимо добавить элементы.\n");
		return;
	}
	value = &queue->front->num;
}

// добавление в конец очереди
void Enqueue(pQueue queue, int *value)
{
	if (queue->size == queue->maxSize)
	{
		printf("Очередь заполнена, необходимо увеличить размер очереди.\n");
		return;
	}
	pQueueNode tmp = (pQueueNode)malloc(sizeof(QueueNode));
	// Задание 2: Добавить в программу «реализация стека на основе односвязного списка» проверку на выделение памяти.
	//	Если память не выделяется, то выводится соответствующее сообщение. 
	//	Постарайтесь создать ситуацию, когда память не будет выделяться (добавлением большого количества данных). Не удалось, полагаю это из-за ограничения в 2ГБ на приложение для Windows 10.
	if (tmp == NULL) // если выделение памяти не выполнилось
	{
		printf("Выделение памяти для нового элемента не удалось.\n");
		return;
	}
	tmp->num = *value;
	tmp->next = NULL;

	if (queue->size == 0)
		queue->front = tmp;
	else
		queue->back->next = tmp;
	queue->back = tmp;
	queue->size++;
}

// возврат значения с удаление элемента из очереди
void Dequeue(pQueue queue, int *value)
{
	if (queue->size == 0)
	{
		printf("Очередь пуста, необходимо добавить элементы.\n");
	}
	pQueueNode first = NULL;
	*value = queue->front->num;
	first = queue->front;
	if (queue->front == queue->back)
	{
		queue->back = NULL;
	}
	queue->front = queue->front->next;
	free(first);
	queue->size--;
}

// печать очереди с первого элемента
void printQueue(pQueue queue)
{
	pQueueNode current = queue->front;
	while (current != NULL)
	{
		printf("посещение %d вершины ", current->num);
		current = current->next;
		if (current != NULL)
		{
			printf("переход в вершину %d\n", current->num);
		}
	}
}

// поиск элемента в очереди
bool findQueue(pQueue queue, int num)
{
	pQueueNode current = queue->front;
	while (current != NULL)
	{
		if (current->num == num)
			return true;
		current = current->next;
	}
	return false;
}

//поиск в ширину
void BFS(pQueue queue, pQueue queueUsed, int numNode, int **graph, int vertexs)
{
	printf("Посетили %d вершину\n", numNode);
	Enqueue(queueUsed, &numNode);
	
	int *row = graph[numNode];

	for (int i = 0; i < vertexs; i++)
	{
		if ((row[i] > 0) && (findQueue(queueUsed, i) == false) && (findQueue(queue, i) == false))
		{
			int val = i;
			printf("- Добавили %d в очередь\n", i);
			Enqueue(queue, &val);
		}
	}

	if (queue->size > 0) {
		int nextNum;
		Dequeue(queue, &nextNum);
		if ((findQueue(queueUsed, nextNum) == false) && (findQueue(queue, nextNum) == false))
			BFS(queue, queueUsed, nextNum, graph, vertexs);
	}
}

// тип структуры стека
typedef struct tagStack
{
	pQueueNode head;
	int size;
	int maxSize;
} Stack;

typedef Stack * pStack;

// добавить элемент в стек
void push(pStack stack, int *value)
{
	if (stack->size == stack->maxSize)
	{
		printf("Стек заполнен, необходимо увеличить размер стека.\n");
		return;
	}
	pQueueNode tmp = (pQueueNode)malloc(sizeof(QueueNode));
	// Задание 2: Добавить в программу «реализация стека на основе односвязного списка» проверку на выделение памяти.
	//	Если память не выделяется, то выводится соответствующее сообщение. 
	//	Постарайтесь создать ситуацию, когда память не будет выделяться (добавлением большого количества данных). Не удалось, полагаю это из-за ограничения в 2ГБ на приложение для Windows 10.
	if (tmp == NULL) // если выделение памяти не выполнилось
	{
		printf("Выделение памяти для нового элемента не удалось.\n");
		return;
	}
	tmp->num = *value;
	tmp->next = stack->head;
	stack->head = tmp;
	stack->size++;
}

// вытаскивание последнего элемента из стека с возвратом значения
void pop(pStack stack, int *value)
{
	if (stack->size == 0)
	{
		printf("Стек пуст, необходимо добавить элементы.\n");
		return;
	}
	pQueueNode next = NULL;
	*value = stack->head->num;
	next = stack->head;
	stack->head = stack->head->next;
	free(next);
	stack->size--;
}

// возврат значения последнего элемента без удаления элемента
void peekStack(pStack stack, int *value)
{
	if (stack->size == 0)
	{
		printf("Стек пуст, необходимо добавить элементы.\n");
		return;
	}
	*value = stack->head->num;
}

void printStack(pStack stack)
{
	pQueueNode current = stack->head;
	while (current != NULL)
	{
		printf("%i", current->num);
		current = current->next;
	}
}

void initStack(pStack stack)
{
	stack->maxSize = 100;
	stack->size = 0;
	stack->head = NULL;
}

// поиск элемента в стеке
bool findStack(pStack queue, int num)
{
	pQueueNode current = queue->head;
	while (current != NULL)
	{
		if (current->num == num)
			return true;
		current = current->next;
	}
	return false;
}

//поиск в глубину
void DFS(pStack stack, pQueue queueUsed, int numNode, int **graph, int vertexs)
{
	printf("Посетили %d вершину\n", numNode);
	Enqueue(queueUsed, &numNode);

	int *row = graph[numNode];

	for (int i = 0; i < vertexs; i++)
	{
		if ((row[i] > 0) && (findQueue(queueUsed, i) == false) && (findStack(stack, i) == false))
		{
			int val = i;
			printf("- Добавили %d в очередь\n", i);
			push(stack, &val);
			DFS(stack, queueUsed, val, graph, vertexs);

			int temp;
			pop(stack, &temp);
		}
	}
}

// Задание 2: Написать функцию обхода графа в ширину.
void solution01()
{
	descriptionTask("Написать функцию обхода графа в ширину.\n");
	// Ввод данных
	char filename[SHRT_MAX];

	printf("\nВведите файл, из которого будут считаны данные: ");
	scanf("%s", filename);

	int V = 0; // число вершин
	int E = 0; // число ребер

	int startVertex = 0;

	int **graph = readMatrixFromFile(filename, &V, &E);
	printGraph(graph, V);

	pQueue queue = (pQueue)malloc(sizeof(Queue));
	initQueue(queue);
	pQueue queueUsed = (pQueue)malloc(sizeof(Queue));
	initQueue(queueUsed);

	BFS(queue, queueUsed, startVertex, graph, V);

	free(queue);
	//freeGraph(graph, V);
	endTask();
}

// Задание 3: Написать рекурсивную функцию обхода графа в глубину.
void solution02()
{
	descriptionTask("Написать рекурсивную функцию обхода графа в глубину.\n");
	// Ввод данных
	char filename[SHRT_MAX];

	printf("\nВведите файл, из которого будут считаны данные: ");
	scanf("%s", filename);

	int V = 0; // число вершин
	int E = 0; // число ребер

	int startVertex = 0;

	int **graph = readMatrixFromFile(filename, &V, &E);
	printGraph(graph, V);

	pStack stack = (pStack)malloc(sizeof(Stack));
	initStack(stack);
	pQueue queueUsed = (pQueue)malloc(sizeof(Queue));
	initQueue(queueUsed);

	DFS(stack, queueUsed, startVertex, graph, V);

	free(stack);
	//freeGraph(graph, V);
	endTask();
}

// Задание 4: *Создать библиотеку функций для работы с графами.
void solution03()
{
	descriptionTask("*Создать библиотеку функций для работы с графами.\n");
	// Ввод данных

	
	endTask();
}