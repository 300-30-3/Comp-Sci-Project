#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include "winbgi2.h"

//Main functions (used in main)
void drawBoard(int width, int height);
void initializeFirstGen(int width, int height, int* numberOfPeople, bool** aliveStatus);
void initializeNextGen(int width, int height, int* numberOfPeople, bool** aliveStatus);

//Other functions
void drawHorizontalLines(int width, int height);
void drawVerticalLines(int width, int height);
void drawPerson(int x, int y);
void killPerson(int x, int y);
bool isAlive(int x, int y, bool** aliveStatus);
int checkAliveNeighbors(int width, int height, int x, int y, bool** aliveStatus);


void main()
{
	int width = GetSystemMetrics(SM_CXFULLSCREEN);
	int height = GetSystemMetrics(SM_CXFULLSCREEN);
	int numberOfPeople = 0;
	bool** aliveStatus;

	aliveStatus = (bool**)malloc(((width / 10) + 1) * sizeof(bool*));
	for (int i = 0; i < ((width / 10) + 1); i++)
	{
		aliveStatus[i] = (bool*)malloc(((height / 10) + 1) * sizeof(bool));
	}

	graphics(width, height);

	drawBoard(width, height);

	initializeFirstGen(width, height, &numberOfPeople, aliveStatus);

	for (int i = 0; i < 100; i++)
	{
		system("@cls || clear");
		printf("Liczba populacji: %d", numberOfPeople);

		animate(1);
		initializeNextGen(width, height, &numberOfPeople, aliveStatus);
	}
	wait();
}

void drawBoard(int width, int height)
{
	drawHorizontalLines(width, height);
	drawVerticalLines(width, height);
}

void initializeFirstGen(int width, int height, int* numberOfPeople, bool** aliveStatus)
{
	srand(time(NULL));

	for (int y = 0; y < height; y += 10)
		for (int x = 0; x < width; x += 10)
			if (rand() % 2 == 1)
			{
				drawPerson(x, y);
				aliveStatus[x / 10][y / 10] = 1;
				(*numberOfPeople)++;
			}
}

void initializeNextGen(int width, int height, int* numberOfPeople, bool** aliveStatus)
{
	(*numberOfPeople) = 0;

	for (int y = 0; y < height; y += 10)
		for (int x = 0; x < width; x += 10)
		{
			int numberOfAliveNeighbors = checkAliveNeighbors(width, height, x, y, aliveStatus);

			if (isAlive(x, y, aliveStatus) == 1 && ( numberOfAliveNeighbors == 2 || numberOfAliveNeighbors == 3))
			{
				drawPerson(x, y);
				aliveStatus[x / 10][y / 10] = 1;
				(*numberOfPeople)++;
			}

			else if(isAlive(x, y, aliveStatus) == 0 && numberOfAliveNeighbors == 3)
			{
				drawPerson(x, y);
				aliveStatus[x / 10][y / 10] = 1;
				(*numberOfPeople)++;
			}

			else
			{
				killPerson(x, y);
				aliveStatus[x / 10][y / 10] = 0;
			}
		}
}

void drawHorizontalLines(int width, int height)
{
	for (int y0 = 0; y0 < height; y0 += 10)
		line(0, y0, width, y0);
}

void drawVerticalLines(int width, int height)
{
	for (int x = 0; x < width; x += 10)
		line(x, 0, x, height);
}

void drawPerson(int x, int y)
{
	int person[10] = { x, y, x + 10, y, x + 10, y + 10,x ,y + 10,x , y};

	setfillstyle(SOLID_FILL, WHITE);
	fillpoly(5, person);
}

void killPerson(int x, int y)
{
	int person[10] = { x, y, x + 10, y, x + 10, y + 10,x ,y + 10,x , y };

	setfillstyle(SOLID_FILL, BLACK);
	fillpoly(5, person);
}

bool isAlive(int x, int y, bool** aliveStatus)
{
	if (aliveStatus[x / 10][y / 10] == 1)
		return 1;
	else
		return 0;
}

int checkAliveNeighbors(int width, int height, int x, int y, bool** aliveStatus)
{
	int numberOfAliveNeighbors = 0;

	if (x != 0 && y != 0)
		if (aliveStatus[x/10 - 1][y/10 - 1] == 1)
			numberOfAliveNeighbors += 1;
	if (x != 0)
		if (aliveStatus[x / 10 - 1][y / 10] == 1)
			numberOfAliveNeighbors += 1;
	if (x != 0 && (y/10) < (height/10))
		if (aliveStatus[x/10 - 1][y/10 + 1] == 1)
			numberOfAliveNeighbors += 1;
	if (y != 0)
		if (aliveStatus[x/10][y/10 - 1] == 1)
			numberOfAliveNeighbors += 1;
	if((y/10) < (height/10))
		if (aliveStatus[x/10][y/10 + 1] == 1)
			numberOfAliveNeighbors += 1;
	if (y != 0 && (x/10) < (width/10))
		if (aliveStatus[x/10 + 1][y/10 - 1] == 1)
			numberOfAliveNeighbors += 1;
	if ((x/10) < (width/10))
		if (aliveStatus[x/10 + 1][y/10] == 1)
			numberOfAliveNeighbors += 1;
	if ((x/10) < (width/10) && (y/10) < (height/10))
		if (aliveStatus[x/10 + 1][y/10 + 1] == 1)
			numberOfAliveNeighbors += 1;

	return numberOfAliveNeighbors;
}