#pragma once

#include <vector>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <random>
#include <math.h>
#include <stdio.h>
#include <string>

using namespace std;
enum box_orient
{
	VERTICAL_1,
	VERTICAL_2,
	HORIZONTAL_1,
	HORIZONTAL_2,
};

struct point
{
	int x;
	int y;
	int z;
	point(int a, int b, int c);
};

struct box
{
	int id;
	int width;
	int height;
	int depth;
	bool flag;
	point *position;
	box(int id, int w, int h, int d, bool flag, point* position);
};

struct EMS
{
	point *a;
	point *b;
    int width;
    int height;
    int depth;
	bool flag; //if flag == true --> eliminate this EMS
	EMS();
    EMS(point *a, point *b);
};

struct bin
{
	int width;
	int height;
	int depth;
	vector<box> *boxes;
	vector<EMS> *EMSs;
	bool flag;
	bin(int a, int b, int c);
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

