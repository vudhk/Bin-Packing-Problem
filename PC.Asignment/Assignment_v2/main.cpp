
#include "main.h"

using namespace std;


int main(int argv, char *argv[])
{

}

// Return index of EMS in bin->EMSs
// Return bo - hướng của box
int dftrc_2(box *box, bin *bin, box_orient *bo)
{
	int num_of_EMS = bin->EMSs.count();
	int EMS_idx = -1;
	float maxDist = -1;
	int i, j;
	*bo = -1;
	// Lặp cho mỗi EMS trong bin
	for (i = 0; i < num_of_EMS; i++)
	{
		// Lặp cho 4 hướng của box
		for (j = 0; j < 4; j++)
		{
			box_orient _bo = static_cast<box_orient>(j);
			// Xác định width, height, depth tương ứng với mỗi hướng của box.
			int w, h, d;
			switch (_bo)
			{
				case VERTICAL_1:
					w = box->width;
					h = box->height;
					d = box->depth;
					break;
				case VERTICAL_2:
					w = box->depth;
					h = box->height;
					d = box->width;
					break;
				case HORIZONTAL_1:
					w = box->height;
					h = box->width;
					d = box->depth;
					break;
				case HORIZONTAL_2:
					w = box->height;
					h = box->depth;
					d = box->width;
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
					*bo = _bo;
					EMS_idx = i;
				}
			} 
		}
	}
	return EMS_idx == -1 ? 0 : EMS_idx;
}

// 
void placement(chromosome *chromosome)
{

}
