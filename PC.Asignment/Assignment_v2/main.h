#pragma once

#include <vector>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <random>
#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <string>

enum box_orient
{
	VERTICAL_1 = 0
	VERTICAL_2 = 1
	HORIZONTAL_1 = 2
	HORIZONTAL_2 = 3
};

struct point
{
	int x;
	int y;
	int z;
};

struct box
{
	int id;
	int width;
	int height;
	int depth;
	bool flag;
	point position;
};

struct EMS
{
	point position;
	int width;
	int height;
	int depth;
	bool flag;
};

struct bin
{
	int numOfBox;
	int width;
	int height;
	int depth;
	vector<box> boxes;
	vector<EMS> EMSs;
	bool flag;
};

struct gene
{
	int box_id;
	float value;
};

struct chromosome
{
	int size;
	vector<gene> genes;
	vector<box_orient> bo;
};

struct individual
{
	chromosome chromosome;
	int fitness;
};

EMS *find_EMS(bin *bin);
int dftrc_2(box *box, bin *bin, box_orient *bo);
void placement(chromosome *chromosome);
