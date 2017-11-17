
#include "main.h"

using namespace std;
using std::vector;

#define MAX_POPULATION 100;

vector<box> *boxes;
vector<individual> *population;
int input_size;

int main(int argv, char *argv[])
{
	int i, num_of_box = 10;
	srand(time(NULL));
	boxes = new vector<box>[num_of_box];
}


int genetic_algorithm_run()
{
	int i, j;
	vector<individual> *new_population;
	individual *father, *mother, *child;

	init_population();
	for (i = 0; i < 100; i++)
	{
		new_population = new vector<individual>();
		for (j = 0; j < MAX_POPULATION / 2; j++)
		{
			father = select_parent();
			mother = select_parent();
			child = crossover(father, mother);
			mutation(child);
			new_population->push_back(*child);
		}

		//double start = omp_get_wtime();
		// delete old population
		for (j = 0; j < MAX_POPULATION; j++)
		{
			delete &population->at(j);
		}

		//double elapse = omp_get_wtime() - start;
		// renew population
		population = new_population;
	}
	return find_best_fitness();
}

int find_best_fitness()
{
	int i;
	individual fitnist = population->at(0);
	for (i = 1; i < MAX_POPULATION; i++)
	{
		if (population->at(i).fitness < fitnist->fitness)
		{
			fitnist = population->at(i);
		}
	}
	return fitnist->fitness;
}

void init_population()
{
	int i;
	for (i = 0; i < MAX_POPULATION; i++)
	{
		individual *idv = random_chromosome();
		calc_fitness(idv);
		population->push_back(*idv);
	}
}

individual *select_parent()
{
	int i, num;
	int x = (int)(0.3 * input_size);
	x = x < 1 ? 1 : x;

	num = random_int(0, MAX_POPULATION - 1);
	individual *parent = &population->at(num);

	for (i = 1; i < x; i++)
	{
		num = random_int(0, MAX_POPULATION - 1);
		if (parent->fitness < population->at(num).fitness)
		{
			parent = &population->at(num);
		}
	}
	return parent;
}

individual *crossover(individual *father, individual *mother)
{
	
	
	return father;
}

void mutation(individual *idv)
{
	int i, j;
	i = random_int(0, input_size - 1);
	j = random_int(0, input_size - 1);

	// swap i-th idv's BPS-gene for j-th idv's BPS-gene
	BPS_gene bps_gene_tmp = (*idv->chromosome->BPS)[i];
	(*idv->chromosome->BPS)[i] = (*idv->chromosome->BPS[j]);
	(*idv->chromosome->BPS)[j] = bps_gene_tmp;

	// swap i-th idv's BO-gene for j-th idv's BO-gene
	BO_gene bo_gene_tmp = (*idv->chromosome->VBO)[i];
	(*idv->chromosome->VBO)[i] = (*idv->chromosome->VBO[j]);
	(*idv->chromosome->VBO)[j] = bo_gene_tmp;
}

individual *random_chromosome()
{
	int i, r;
	vector<BPS_gene> *BPS = new vector<BPS_gene>();
	vector<BO_gene> *VBO = new vector<BO_gene>();
	for (i = 0; i < input_size; i++)
	{
		r = random_int(0, input_size - 1);
		BPS_gene bps_gene(boxes->at(r).id);
		BO_gene bo_gene();
		BPS->push_back(bps_gene);
		VBO->push_back(bo_gene);
	}
	chromosome *chromosome = new chromosome(BPS, VBO);
	individual *idv = new individual(chromosome);
}

void calc_fitness(individual *idv)
{
	idv->fitness = placement(idv->chromosome);
}

// Đặt lần lượt các box vào bin
int placement(chromosome *chromosome)
{
	// Initialization
	int num_of_bin;
	vector<int> bins();
	bins.push_back(0);
	int i, j, box_id, EMS_idx, bin_idx;
	for (i = 0; i < input_size; i++)
	{
		// Chọn box
		box_id = chromosome->BPS->at(i).box_id;
		// Chọn Bin và EMS
		EMS_idx = -1;
		bin_idx = -1;
		for (j = 0; j < bins.count(); j++)
		{
			EMS_idx = dftrc_2(&boxes->at([chromosome->BPS->at(i).box_id]), &bins.at(j));
			if (EMS_idx >= 0)
			{
				bin_idx = j;
				break;
			}
		}
		if (bin_idx < 0)
		{
			// Mở một bin mới
			bin_idx = bins.count();
			bins.push_back(bin_idx);
			EMS_idx = 0;
		}

		// Chọn hướng của box 0-đứng, 1-nằm
		float bo_value = floor(chromosome->VBO->at(i).value * 2);
		bo_value = bo_value >= 2 ? 1: bo_value;
		// Box packing
		chromosome->BPS->at(i).flag = true;
		chromosome->BPS->at(i).position.x = bins.at(bin_idx).EMSs->at(EMS_idx).position.x;
		chromosome->BPS->at(i).position.y = bins.at(bin_idx).EMSs->at(EMS_idx).position.y;
		chromosome->BPS->at(i).position.z = bins.at(bin_idx).EMSs->at(EMS_idx).position.z;
		chromosome->VBO->at(i).value = bo_value;

		bins.at(bin_idx).boxes->push_back(chromosome->BPS->at(i));

		// Cập nhật thông tin trạng thái cho danh sách EMS
		delete bins.at(bin_idx).EMSs
		bins.at(bin_idx).EMSs = find_EMS(&bins.at(bin_idx));
	} 
	num_of_bin = bin.count();
	delete &bins;
	return num_of_bin;
}

// Return index of EMS in bin->EMSs
// Return bo - hướng của box
int dftrc_2(box *box, bin *bin)
{
	int num_of_EMS = bin->EMSs->count();
	int EMS_idx = -1;
	float maxDist = -1;
	int i, j, k;
	// Lặp cho mỗi EMS trong bin
	for (i = 0; i < num_of_EMS; i++)
	{
		// Lặp cho 6 hướng của box
		for (j = 0; j < 3; j++)
		{
			box_orient _bo = static_cast<box_orient>(j);
			for (k = 0; k < 2; k++)
			{
				// Xác định width, height, depth tương ứng với mỗi hướng của box.
				int w, h, d;
				switch (_bo)
				{
					case FRONT:
						{
							if (k == 0)
							{
								w = box->width;
								h = box->height;
								d = box->depth;
							}
							else 
							{
								w = box->height;
								h = box->width;
								d = box->depth;
							}
						}
						break;
					case SIDE:
						{
							if (k == 0)
							{
								w = box->depth;
								h = box->height;
								d = box->width;
							}
							else 
							{
								w = box->height;
								h = box->depth;
								d = box->width;
							}
						}
						break;
					case BOTTOM:
						{
							if (k == 0)
							{
								w = box->width;
								h = box->depth;
								d = box->height;
							}
							else 
							{
								w = box->depth;
								h = box->width;
								d = box->height;
							}
						}
						break;
				}

				// if box fits i-th EMS of bin using BO
				if (w <= bin->EMSs->at(EMS_idx).width &&
					h <= bin->EMSs->at(EMS_idx).height &&
					d <= bin->EMSs->at(EMS_idx).depth)
				{
					float dist = pow(bin->width - bin->EMSs.at(EMS_idx).position.x - w) +
								pow(bin->height - bin->EMSs.at(EMS_idx).position.y - h) +
								pow(bin->depth - bin->EMSs.at(EMS_idx).position.z - d);
					if (dist > maxDist)
					{
						maxDist = dist;
						EMS_idx = i;
					}
				}
			} 
		}
	}
	return EMS_idx;
}


vector<EMS> *find_EMS(bin *bin)
{
	return new vector<EMS>();
}

int random_int(int start, int end)
{
	return rand() % (end - start + 1) + start;
}

float random_float(float start, float end)
{
	return rand() % (end - start + 1) + start;
}


point::point()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
box::box(int id)
{
	this->id = id;
	this->width = 0;
	this->height = 0;
	this->depth = 0;
}
EMS::EMS()
{
	this->position = new point();
	this->width = 0;
	this->height = 0;
	this->depth = 0;
	this->flag = false;
}
bin::bin()
{
	this->width = 0;
	this->height = 0;
	this->depth = 0;
	this->boxes = NULL;
	this->EMSs = NULL;
	this->flag = false;
}
BPS_gene::BPS_gene(int box_id)
{
	this->box_id = box_id;
	this->value = random_float(0, 1);
	this->flag = false;
	this->position = new point();
}
BO_gene::BO_gene()
{
	this->bo = static_cast<box_orient>(random_int(0, 2));
	this->value = random_float(0, 1);
}
chromosome::chromosome(BPS_gene *BPS_gene, BO_gene *BO_gene)
{
	this->BPS = BPS_gene;
	this->VBO = BO_gene;
}
individual::individual(chromosome *chromosome)
{
	this->chromosome = chromosome;
	this->fitness = -1;
}
