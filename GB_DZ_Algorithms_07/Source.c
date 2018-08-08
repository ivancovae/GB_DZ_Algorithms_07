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

		int ** graph;
		int posY = 0;

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
					graph = (int **)malloc(sizeof(int *) * _V);
					continue;
				}
				graph[posY] = (int *)malloc(sizeof(int) * _V);

				for (int i = 0; i < strlen(data); i++)
				{
					char elem[SHRT_MAX];
					int j = 0;
					while (data[i] != ' ' && data[i] != '\0')
					{
						elem[j++] = data[i++];
					}
					elem[j] = '\0';
					int temp = atoi(elem);
					if (temp > 0)
					{
						_E++;
					}
					graph[posY][posX++] = temp;
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
	int i;

	for (i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			printf("%d ", graph[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < V; i++)
		free(graph[i]);
	free(graph);
	
	endTask();
}

// Задание 2: Написать рекурсивную функцию обхода графа в глубину.
void solution01()
{
	descriptionTask("Написать рекурсивную функцию обхода графа в глубину.\n");
	// Ввод данных
	

	endTask();
}

// Задание 3: Написать функцию обхода графа в ширину.
void solution02()
{
	descriptionTask("Написать функцию обхода графа в ширину.\n");
	// Ввод данных
	
	
	endTask();
}

// Задание 4: *Создать библиотеку функций для работы с графами.
void solution03()
{
	descriptionTask("*Создать библиотеку функций для работы с графами.\n");
	// Ввод данных

	
	endTask();
}