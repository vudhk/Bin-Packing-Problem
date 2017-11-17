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
	FRONT = 0
	SIDE = 1
	BOTTOM = 2
	UNKNOWN = 3
};

struct point
{
	int x;
	int y;
	int z;
	point();
};

struct box
{
	int id;
	int width;
	int height;
	int depth;
	box(int id);
};

struct EMS
{
	point *position;
	int width;
	int height;
	int depth;
	bool flag;
	EMS();
};

struct bin
{
	int width;
	int height;
	int depth;
	vector<BPS_gene> *boxes;
	vector<EMS> *EMSs;
	bool flag;
	bin();
};

struct BPS_gene
{
	int box_id;
	float value;
	bool flag;
	point *position;
	BPS_gene(int box_id);
};

struct BO_gene
{
	box_orient bo;
	float value;
	BO_gene();
}

struct chromosome
{
	vector<BPS_gene> *BPS;
	vector<BO_gene> *VBO;
	chromosome();
};

struct individual
{
	chromosome *chromosome;
	int fitness;
	individual();
};

vector<EMS> *find_EMS(bin *bin);
int dftrc_2(box *box, bin *bin);
void placement(chromosome *chromosome);
