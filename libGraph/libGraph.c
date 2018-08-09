#include "libGraph.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>

int **readMatrixFromFile(char *filename, int *V, int *E)
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