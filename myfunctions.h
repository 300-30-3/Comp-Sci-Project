#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include "winbgi2.h"
#include "myfunctions.h"

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