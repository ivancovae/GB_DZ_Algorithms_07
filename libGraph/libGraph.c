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
		puts("�� ������� ������� ����!\n");
		return NULL;
	}
	else
	{
		char data[SHRT_MAX];
		int _V = 0; // ����� ������
		int _E = 0; // ����� �����

		int **graph = NULL;
		int posY = 0;
		int i = 0;

		// �������
		printf("���������: \n");

		// ������ ������� ��������� ����� �� �����
		// ������ ������� ���������� ������
		// �� ��������� ������ ��������� ������� ���������
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

		printf("\n���� ����� %d ������ � %d �����\n", _V, _E);
		*V = _V;
		*E = _E;
		return graph;
	}
}

void printGraph(int **graph, int vertexs)
{
	for (int i = 0; i < vertexs; i++)
	{
		printf("%4d ������� - ", i);
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
		// �������� � �������� ���������� ��������
		free(graph);
	}
}

// ������������� �������
void initQueue(pQueue queue)
{
	queue->maxSize = 100;
	queue->size = 0;
	queue->front = NULL;
	queue->back = NULL;
}

// ������� �������
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

// ������� �������� ������� �������� ��� �������� ��������
void Peek(pQueue queue, int *value)
{
	if (queue->size == 0)
	{
		printf("������� �����, ���������� �������� ��������.\n");
		return;
	}
	value = &queue->front->num;
}

// ���������� � ����� �������
void Enqueue(pQueue queue, int *value)
{
	if (queue->size == queue->maxSize)
	{
		printf("������� ���������, ���������� ��������� ������ �������.\n");
		return;
	}
	pQueueNode tmp = (pQueueNode)malloc(sizeof(QueueNode));
	// ������� 2: �������� � ��������� ����������� ����� �� ������ ������������ ������ �������� �� ��������� ������.
	//	���� ������ �� ����������, �� ��������� ��������������� ���������. 
	//	������������ ������� ��������, ����� ������ �� ����� ���������� (����������� �������� ���������� ������). �� �������, ������� ��� ��-�� ����������� � 2�� �� ���������� ��� Windows 10.
	if (tmp == NULL) // ���� ��������� ������ �� �����������
	{
		printf("��������� ������ ��� ������ �������� �� �������.\n");
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

// ������� �������� � �������� �������� �� �������
void Dequeue(pQueue queue, int *value)
{
	if (queue->size == 0)
	{
		printf("������� �����, ���������� �������� ��������.\n");
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

// ������ ������� � ������� ��������
void printQueue(pQueue queue)
{
	pQueueNode current = queue->front;
	while (current != NULL)
	{
		printf("��������� %d ������� ", current->num);
		current = current->next;
		if (current != NULL)
		{
			printf("������� � ������� %d\n", current->num);
		}
	}
}

// ����� �������� � �������
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

//����� � ������
void BFS(pQueue queue, pQueue queueUsed, int numNode, int **graph, int vertexs)
{
	printf("�������� %d �������\n", numNode);
	Enqueue(queueUsed, &numNode);

	int *row = graph[numNode];

	for (int i = 0; i < vertexs; i++)
	{
		if ((row[i] > 0) && (findQueue(queueUsed, i) == false) && (findQueue(queue, i) == false))
		{
			int val = i;
			printf("- �������� %d � �������\n", i);
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

// �������� ������� � ����
void push(pStack stack, int *value)
{
	if (stack->size == stack->maxSize)
	{
		printf("���� ��������, ���������� ��������� ������ �����.\n");
		return;
	}
	pQueueNode tmp = (pQueueNode)malloc(sizeof(QueueNode));
	// ������� 2: �������� � ��������� ����������� ����� �� ������ ������������ ������ �������� �� ��������� ������.
	//	���� ������ �� ����������, �� ��������� ��������������� ���������. 
	//	������������ ������� ��������, ����� ������ �� ����� ���������� (����������� �������� ���������� ������). �� �������, ������� ��� ��-�� ����������� � 2�� �� ���������� ��� Windows 10.
	if (tmp == NULL) // ���� ��������� ������ �� �����������
	{
		printf("��������� ������ ��� ������ �������� �� �������.\n");
		return;
	}
	tmp->num = *value;
	tmp->next = stack->head;
	stack->head = tmp;
	stack->size++;
}

// ������������ ���������� �������� �� ����� � ��������� ��������
void pop(pStack stack, int *value)
{
	if (stack->size == 0)
	{
		printf("���� ����, ���������� �������� ��������.\n");
		return;
	}
	pQueueNode next = NULL;
	*value = stack->head->num;
	next = stack->head;
	stack->head = stack->head->next;
	free(next);
	stack->size--;
}

// ������� �������� ���������� �������� ��� �������� ��������
void peekStack(pStack stack, int *value)
{
	if (stack->size == 0)
	{
		printf("���� ����, ���������� �������� ��������.\n");
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

// ����� �������� � �����
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

//����� � �������
void DFS(pStack stack, pQueue queueUsed, int numNode, int **graph, int vertexs)
{
	printf("�������� %d �������\n", numNode);
	Enqueue(queueUsed, &numNode);

	int *row = graph[numNode];

	for (int i = 0; i < vertexs; i++)
	{
		if ((row[i] > 0) && (findQueue(queueUsed, i) == false) && (findStack(stack, i) == false))
		{
			int val = i;
			printf("- �������� %d � �������\n", i);
			push(stack, &val);
			DFS(stack, queueUsed, val, graph, vertexs);

			int temp;
			pop(stack, &temp);
		}
	}
}