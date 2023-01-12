#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include "winbgi2.h"
#include "myfunctions.h"

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