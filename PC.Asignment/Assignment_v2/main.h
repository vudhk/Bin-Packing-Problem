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

using namespace std;
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
    point(int a, int b, int c);
    point();
    ~point();
};

struct box
{
    int id;
    int width;
    int height;
    int depth;
    bool flag;
    box(int id, int w, int h, int d, bool flag);
    box(int id);
    ~box();
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
    ~EMS();
};

struct BPS_gene
{
    int box_id;
    float value;
    bool flag;
    point *position;
    void dispose();
    BPS_gene(int box_id);
    ~BPS_gene();
};

struct BO_gene
{
    box_orient bo;
    float value;
    BO_gene();
    ~BO_gene();
};

struct bin
{
    int width;
    int height;
    int depth;
    vector<BPS_gene*> *boxes;
    vector<EMS*> *EMSs;
    bool flag;
    bin();
    bin(int a, int b, int c);
    ~bin();
};

struct chromosome
{
    vector<BPS_gene*> *BPS;
    vector<BO_gene*> *VBO;
    chromosome(vector<BPS_gene*> *BPS_gene, vector<BO_gene*> *BO_gene);
    ~chromosome();
};

struct individual
{
    chromosome *chrom;
    int fitness;
    individual(chromosome *chrom);
    ~individual();
};

vector<EMS*> *find_EMS(bin *bin);
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
int random_int(int start, int end);
float random_float(float start, float end);
void print(vector<float> *vt);
int put_box_into_pin(bin *bin, BPS_gene *ibox);
void print_EMSs(vector<EMS*> *EMSs);
void print_point(point *point);
vector<EMS*> *generate_new_EMSs(bin *bin, BPS_gene *box);
bool coincide_points(point *a, point *b);
vector<point*> find_points(BPS_gene *box);
int cross_checking_EMS(vector<EMS*> *EMSs);
bool is_ems2_includes_ems1(EMS *ems1, EMS *ems2);
vector<EMS*> diff_process(EMS *ems, BPS_gene *box);
bool is_err_EMS(EMS ems);
bool is_infinity_thickness_EMS(EMS *ems);
void clean_population();
void free_mem();