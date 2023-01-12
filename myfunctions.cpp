#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include "winbgi2.h"
#include "myfunctions.h"

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

			if (isAlive(x, y, aliveStatus) == 1 && (numberOfAliveNeighbors == 2 || numberOfAliveNeighbors == 3))
			{
				drawPerson(x, y);
				aliveStatus[x / 10][y / 10] = 1;
				(*numberOfPeople)++;
			}

			else if (isAlive(x, y, aliveStatus) == 0 && numberOfAliveNeighbors == 3)
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
	int person[10] = { x, y, x + 10, y, x + 10, y + 10,x ,y + 10,x , y };

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
		if (aliveStatus[x / 10 - 1][y / 10 - 1] == 1)
			numberOfAliveNeighbors += 1;
	if (x != 0)
		if (aliveStatus[x / 10 - 1][y / 10] == 1)
			numberOfAliveNeighbors += 1;
	if (x != 0 && (y / 10) < (height / 10))
		if (aliveStatus[x / 10 - 1][y / 10 + 1] == 1)
			numberOfAliveNeighbors += 1;
	if (y != 0)
		if (aliveStatus[x / 10][y / 10 - 1] == 1)
			numberOfAliveNeighbors += 1;
	if ((y / 10) < (height / 10))
		if (aliveStatus[x / 10][y / 10 + 1] == 1)
			numberOfAliveNeighbors += 1;
	if (y != 0 && (x / 10) < (width / 10))
		if (aliveStatus[x / 10 + 1][y / 10 - 1] == 1)
			numberOfAliveNeighbors += 1;
	if ((x / 10) < (width / 10))
		if (aliveStatus[x / 10 + 1][y / 10] == 1)
			numberOfAliveNeighbors += 1;
	if ((x / 10) < (width / 10) && (y / 10) < (height / 10))
		if (aliveStatus[x / 10 + 1][y / 10 + 1] == 1)
			numberOfAliveNeighbors += 1;

	return numberOfAliveNeighbors;
}