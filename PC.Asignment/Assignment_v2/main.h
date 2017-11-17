#pragma once

#include <vector>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>

using std::vector;

enum box_orient
{
	FRONT = 0,
	SIDE = 1,
	BOTTOM = 2,
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

struct chromosome
{
	vector<BPS_gene> *BPS;
	vector<BO_gene> *VBO;
	chromosome(vector<BPS_gene> *BPS_gene, vector<BO_gene> *BO_gene);
};

struct individual
{
	chromosome *chrom;
	int fitness;
	individual(chromosome *chrom);
};

vector<EMS> *find_EMS(bin *bin);
int dftrc_2(box *box, bin *bin);
int placement(chromosome *chrom);
int genetic_algorithm_run();
int find_best_fitness();
void init_population();
individual *select_parent();
individual *crossover(individual *father, individual *mother);
void mutation(individual *idv);
individual *random_chromosome();
void calc_fitness(individual *idv);
int placement(chromosome *chrom);
int dftrc_2(box *box, bin *bin);
vector<EMS> *find_EMS(bin *bin);
int random_int(int start, int end);
float random_float(float start, float end);
void print(vector<float> *vt);