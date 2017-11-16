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
	VERTICAL_1
	VERTICAL_2
	HORIZONTAL_1
	HORIZONTAL_2
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
	gene *genes;
	box_orient *bo;
};

struct individual
{
	chromosome chromosome;
	int fitness;
};

EMS *find_EMS(bin *bin);
EMS *dftrc_2(box *box, bin *bin, box_orient *bo);
void placement(chromosome *chromosome);
