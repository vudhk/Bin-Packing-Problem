
#include "main.h"

using namespace std;

#define MAX_POPULATION 100

// global variable
vector<box> *boxes;
vector<individual> *population;
int input_size = 10;
int bin_width = 20;
int bin_height = 20;
int bin_depth = 20;

// main function
int main(int argv, char **argc)
{
	int i;
	srand(time(NULL));

	cout << "Init the list of boxes..." << endl;
	boxes = new vector<box>();
	for (i = 0; i < input_size; i++)
	{
		box box(i);
		box.width = random_int(1, 10);
		box.height = random_int(1, 10);
		box.depth = random_int(1, 10);
		boxes->push_back(box);
	}

	cout << "Genetic algorithm is running..." << endl;
	int solution = genetic_algorithm_run();
	cout << "solution: " << solution << " bin(s)" << endl;

	return 0;
}

// Genetic algorithm
int genetic_algorithm_run()
{
	int i, j;
	vector<individual> *new_population;
	individual *father, *mother, *child;

	cout << "Init population..." << endl;
	init_population();
	for (i = 0; i < 50; i++)
	{
		cout << "--- Iteration " << i + 1 << endl;
		new_population = new vector<individual>();
		for (j = 0; j < MAX_POPULATION; j++)
		{
			//cout << "--0: " << population->size() <<endl;
			father = select_parent();
			mother = select_parent();
			//cout << "--1" <<endl;
			child = crossover(father, mother);
			mutation(child);
			//cout << "--2" <<endl;
			calc_fitness(child);
			//cout << "--3" <<endl;
			new_population->push_back(*child);
			//cout << "--4" <<endl;
		}
		//cout << "--5" <<endl;
		//double start = omp_get_wtime();
		// delete old population
		for (j = 0; j < MAX_POPULATION; j++)
		{
			//delete population;
		}
		//cout << "--6" << endl;
		//double elapse = omp_get_wtime() - start;
		// renew population
		population = new_population;
	}
	cout << "Find the best fitness..." << endl;
	return find_best_fitness();
}

int find_best_fitness()
{
	int i;
	individual fitnist = population->at(0);
	for (i = 1; i < MAX_POPULATION; i++)
	{
		if (population->at(i).fitness < fitnist.fitness)
		{
			fitnist = population->at(i);
		}
	}
	return fitnist.fitness;
}

void init_population()
{
	int i;
	population = new vector<individual>();
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
	vector<BPS_gene> *bps_genes = new vector<BPS_gene>();
	vector<BO_gene> *bo_genes = new vector<BO_gene>();
	int j, k, r;
	bool flag;
	individual *parent;
	for (j = 0; j < input_size; j++)
	{
		for (r = 0; r < 2; r++)
		{
			parent = r == 0 ? father : mother;
			//cout << "id: " << parent->chrom->BPS->at(j).box_id << endl;
			flag = false;
			for (k = 0; k < bps_genes->size(); k++)
			{
				if (bps_genes->at(k).box_id == parent->chrom->BPS->at(j).box_id)
				{
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				//cout << "--: " << parent->chrom->BPS->at(j).box_id << endl;
				BPS_gene *bps_gen = new BPS_gene(parent->chrom->BPS->at(j).box_id);
				bps_gen->value = parent->chrom->BPS->at(j).value;
				bps_genes->push_back(*bps_gen);

				BO_gene *bo_gene = new BO_gene();
				bo_gene->value = parent->chrom->VBO->at(j).value;
				bo_gene->bo = parent->chrom->VBO->at(j).bo;
				bo_genes->push_back(*bo_gene);
			}
		}
	}
	//cout << "size: " << bo_genes->size() << endl;
	individual *indivChild = new individual(new chromosome(bps_genes, bo_genes));
	return indivChild;
}

void mutation(individual *idv)
{
	int i, j;
	i = random_int(0, input_size - 1);
	j = random_int(0, input_size - 1);

	// swap i-th idv's BPS-gene for j-th idv's BPS-gene
	BPS_gene bps_gene_tmp = (*idv->chrom->BPS)[i];
	(*idv->chrom->BPS)[i] = (*idv->chrom->BPS)[j];
	(*idv->chrom->BPS)[j] = bps_gene_tmp;

	// swap i-th idv's BO-gene for j-th idv's BO-gene
	BO_gene bo_gene_tmp = (*idv->chrom->VBO)[i];
	(*idv->chrom->VBO)[i] = (*idv->chrom->VBO)[j];
	(*idv->chrom->VBO)[j] = bo_gene_tmp;
}

individual *random_chromosome()
{
	int i,j,tmp;
	vector<BPS_gene> *BPS = new vector<BPS_gene>();
	vector<BO_gene> *VBO = new vector<BO_gene>();
	int arr[input_size];
	for (i = 0; i < input_size; i++)
	{
		arr[i] = i;
	}
	for (i = 0; i < input_size; i++)
	{
		j = random_int(1, input_size) - 1;
		//swap
		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
	for (i = 0; i < input_size; i++)
	{
		BPS_gene *bps_gene = new BPS_gene(boxes->at(arr[i]).id);
		BO_gene *bo_gene = new BO_gene();
		BPS->push_back(*bps_gene);
		VBO->push_back(*bo_gene);
	}

	chromosome *chrom = new chromosome(BPS, VBO);
	individual *idv = new individual(chrom);
}

void calc_fitness(individual *idv)
{
	idv->fitness = placement(idv->chrom);
}

// Đặt lần lượt các box vào bin
int placement(chromosome *chrom)
{
	//cout << "placement-1" << endl;
	// Initialization
	int num_of_bin;
	vector<bin> *bins = new vector<bin>();
	bins->push_back(*new bin());
	int i, j, box_id, EMS_idx, bin_idx;
	for (i = 0; i < input_size; i++)
	{
		//cout << "placement-1" << endl;

		// Chọn box
		box_id = chrom->BPS->at(i).box_id;
		// Chọn Bin và EMS
		EMS_idx = -1;
		bin_idx = -1;
		for (j = 0; j < bins->size(); j++)
		{
			//cout << "placement-2" << endl;
			EMS_idx = dftrc_2(&boxes->at(chrom->BPS->at(i).box_id), &bins->at(j));
			//cout << "placement-3: " << EMS_idx << endl;
			if (EMS_idx >= 0)
			{
				bin_idx = j;
				break;
			}
		}
		//cout << "placement-4" << endl;

		if (bin_idx < 0)
		{
			// Mở một bin mới
			bin_idx = bins->size();
			bins->push_back(*new bin());
			EMS_idx = 0;
		}
		//cout << "placement-5" << endl;
		// Chọn hướng của box 0-đứng, 1-nằm
		//cout << chrom->VBO->size() << endl;
		float bo_value = floor(chrom->VBO->at(i).value * 2);
		bo_value = bo_value >= 2 ? 1: bo_value;
		//cout << "placement-5" << endl;
		// Box packing
		chrom->BPS->at(i).flag = true;
		chrom->BPS->at(i).position->x = bins->at(bin_idx).EMSs->at(EMS_idx).position->x;
		chrom->BPS->at(i).position->y = bins->at(bin_idx).EMSs->at(EMS_idx).position->y;
		chrom->BPS->at(i).position->z = bins->at(bin_idx).EMSs->at(EMS_idx).position->z;
		chrom->VBO->at(i).value = bo_value;

		bins->at(bin_idx).boxes->push_back(chrom->BPS->at(i));

		// Cập nhật thông tin trạng thái cho danh sách EMS
		delete bins->at(bin_idx).EMSs;
		bins->at(bin_idx).EMSs = find_EMS(&bins->at(bin_idx));
		//cout << "placement-6 : "<< i << endl;
	} 
	num_of_bin = bins->size();
	delete bins;
	//cout << "placement-7" << endl;
	return num_of_bin;
}

// Return index of EMS in bin->EMSs
int dftrc_2(box *box, bin *bin)
{
	if (bin->EMSs == NULL)
		return -1;
	int num_of_EMS = bin->EMSs->size();
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
				if (w <= bin->EMSs->at(i).width &&
					h <= bin->EMSs->at(i).height &&
					d <= bin->EMSs->at(i).depth)
				{
					float dist = pow(bin->width - bin->EMSs->at(i).position->x - w, 2) +
								pow(bin->height - bin->EMSs->at(i).position->y - h, 2) +
								pow(bin->depth - bin->EMSs->at(i).position->z - d, 2);
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
	return new vector<EMS>(1, *new EMS());
}

int random_int(int start, int end)
{
	return rand() % (end - start + 1) + start;
}

float random_float(float start, float end)
{
	return (rand() % ((int)((end - start) * 1000) + 1)) / 1000.0 + start;
}

void print(vector<float> *vt)
{
	int i;
	cout << "[" << vt->at(0); 
	for (i = 1; i < vt->size(); ++i)
	{
		cout << ", " << vt->at(i);
	}
	cout << "]" << endl;
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
	this->width = bin_width;
	this->height = bin_height;
	this->depth = bin_depth;
	this->boxes = new vector<BPS_gene>();
	this->EMSs = new vector<EMS>();
	this->EMSs->push_back(*new EMS());
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
chromosome::chromosome(vector<BPS_gene> *BPS_gene, vector<BO_gene> *BO_gene)
{
	this->BPS = BPS_gene;
	this->VBO = BO_gene;
}
individual::individual(chromosome *chrom)
{
	this->chrom = chrom;
	this->fitness = -1;
}


