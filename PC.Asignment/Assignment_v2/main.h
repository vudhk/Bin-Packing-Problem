#pragma once

#include <vector>
#include <iostream>
#include <stdio.h>
#include <time.h>
<<<<<<< HEAD
#include <random>
=======
>>>>>>> 45ccb9aea20ac4732dab4a0db7bb9c3cc7572fee
#include <math.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>

using std::vector;

using namespace std;
enum box_orient
{
<<<<<<< HEAD
	VERTICAL_1,
	VERTICAL_2,
	HORIZONTAL_1,
	HORIZONTAL_2,
=======
	FRONT = 0,
	SIDE = 1,
	BOTTOM = 2,
	UNKNOWN = 3
>>>>>>> 45ccb9aea20ac4732dab4a0db7bb9c3cc7572fee
};

struct point
{
	int x;
	int y;
	int z;
<<<<<<< HEAD
	point(int a, int b, int c);
=======
	point();
>>>>>>> 45ccb9aea20ac4732dab4a0db7bb9c3cc7572fee
};

struct box
{
	int id;
	int width;
	int height;
	int depth;
<<<<<<< HEAD
	bool flag;
	point *position;
	box(int id, int w, int h, int d, bool flag, point* position);
=======
	box(int id);
>>>>>>> 45ccb9aea20ac4732dab4a0db7bb9c3cc7572fee
};

struct EMS
{
<<<<<<< HEAD
	point *a;
	point *b;
    int width;
    int height;
    int depth;
	bool flag; //if flag == true --> eliminate this EMS
	EMS();
    EMS(point *a, point *b);
=======
	point *position;
	int width;
	int height;
	int depth;
	bool flag;
	EMS();
>>>>>>> 45ccb9aea20ac4732dab4a0db7bb9c3cc7572fee
};

struct BPS_gene
{
<<<<<<< HEAD
	int width;
	int height;
	int depth;
	vector<box> *boxes;
	vector<EMS> *EMSs;
	bool flag;
	bin(int a, int b, int c);
=======
	int box_id;
	float value;
	bool flag;
	point *position;
	BPS_gene(int box_id);
>>>>>>> 45ccb9aea20ac4732dab4a0db7bb9c3cc7572fee
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

<<<<<<< HEAD
EMS *find_EMS(bin *bin);
EMS *dftrc_2(box *box, bin *bin, box_orient *bo);
void placement(chromosome *chromosome);

=======
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
>>>>>>> 45ccb9aea20ac4732dab4a0db7bb9c3cc7572fee
