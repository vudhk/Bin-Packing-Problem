
#include "main.h"

using namespace std;



bool is_infinity_thickness_EMS(EMS *ems){
    point *a = ems->a;
    point *b = ems->b;
    if ((a->x >= b->x)||(a->y >= b->y)||(a->z >= b->z))
        return true;
    return false;
}
bool is_err_EMS(EMS ems){
    return true;
}
box::box(int id, int w, int h, int d, bool flag, point* position){
    this->id = id;
    this->width = w;
    this->height = h;
    this->depth = d;
    this->flag = flag;
    this->position = position;
}
bin::bin(int a, int b, int c){
    this->width = a;
    this->height = b;
    this->depth = c;
    
    EMS temp_ems(new point(0,0,0),new point(a,b,c));
    vector<EMS> *vector_EMSs = new vector<EMS>();
    vector_EMSs->push_back(temp_ems);
    
    this->EMSs = vector_EMSs;
    this->boxes = new vector<box>();
    
}
point::point(int a, int b, int c){
    this->x = a;
    this->y = b;
    this->z = c;
}
EMS::EMS(){
    
}
EMS::EMS(point *a, point *b){
    this->a = a;
    this->b = b;
    this->width = b->x - a->x;
    this->height = b->y - a->y;
    this->depth = b->z - a->z;
    this->flag = false;
}
vector<EMS> diff_process(EMS *ems, box *box){ // chua clear ems
    int x1 = ems->a->x;
    int y1 = ems->a->y;
    int z1 = ems->a->z;
    int x2 = ems->b->x;
    int y2 = ems->b->y;
    int z2 = ems->b->z;
    
    int x3 = box->position->x;
    int y3 = box->position->y;
    int z3 = box->position->z;
    int x4 = x3 + box->width;
    int y4 = y3 + box->height;
    int z4 = z3 + box->depth;
    
    if (x3<x1) x3 = x1;
    if (x4<x1) x4 = x1;
    if (x3>x2) x3 = x2;
    if (x4>x2) x4 = x2;
    
    if (y3<y1) y3 = y1;
    if (y4<y1) y4 = y1;
    if (y3>y2) y3 = y2;
    if (y4>y2) y4 = y2;
    
    if (z3<z1) z3 = z1;
    if (z4<z1) z4 = z1;
    if (z3>z2) z3 = z2;
    if (z4>z2) z4 = z2;
    
    vector<EMS> EMSs;
    EMS temp_ems[6];
    temp_ems[0] = *new EMS(new point(x1,y1,z1),new point(x3,y2,z2));
    temp_ems[1] = *new EMS(new point(x4,y1,z1),new point(x2,y2,z2));
    temp_ems[2] = *new EMS(new point(x1,y1,z1),new point(x2,y3,z2));
    temp_ems[3] = *new EMS(new point(x1,y4,z1),new point(x2,y2,z2));
    temp_ems[4] = *new EMS(new point(x1,y1,z1),new point(x2,y2,z3));
    temp_ems[5] = *new EMS(new point(x1,y1,z4),new point(x2,y2,z2));
    
    for (int i=0;i<6;i++){
        if(!is_infinity_thickness_EMS(&temp_ems[i]))
            EMSs.push_back(temp_ems[i]);
    }
    
    return EMSs;
}

bool is_ems2_includes_ems1(EMS *ems1, EMS *ems2){
    int x1 = ems1->a->x;
    int y1 = ems1->a->y;
    int z1 = ems1->a->z;
    int x2 = ems1->b->x;
    int y2 = ems1->b->y;
    int z2 = ems1->b->z;
    
    int x3 = ems2->a->x;
    int y3 = ems2->a->y;
    int z3 = ems2->a->z;
    int x4 = ems2->b->x;
    int y4 = ems2->b->y;
    int z4 = ems2->b->z;
    
    if((x1>=x3) && (y1>=y3) && (z1>=z3) && (x2<=x4) && (y2<=y4) && (z2<=z4))
        return true;
    return false;
}
int cross_checking_EMS(vector<EMS> *EMSs){
    int i,j;
    for (i=0;i<EMSs->size();i++){
        for (j=0;j<EMSs->size();j++){
            if (j==i) continue;
            if (is_ems2_includes_ems1(&EMSs->at(i),&EMSs->at(j)))
                EMSs->at(i).flag = true;
        }
    }
    for (i=0;i<EMSs->size();i++){
    }
    for (i=EMSs->size()-1;i>=0;i--){
        if (EMSs->at(i).flag == true)
            EMSs->erase(EMSs->begin() +i);
    }
    return 0;
}

vector<point> find_points(box *box){
    int x = box->position->x;
    int y = box->position->y;
    int z = box->position->z;
    point RBF = point(x+box->width,y,z); //Point Right Bot Front
    point LTF = point(x,y+box->height,z);//Point Left Top Front
    point LBB = point(x,y,z+box->depth);//Point Left Bot Back
    vector<point> points;
    points.push_back(RBF);
    points.push_back(LTF);
    points.push_back(LBB);
    return points;
}

bool coincide_points(point *a, point *b){
    if((a->x != b->x)||(a->y != b->y)||(a->z != b->z))
        return false;
    return true;
}

vector<EMS> *generate_new_EMSs(bin *bin,box *box){
    int i;
    //     int numOfBox = bin->numOfBox;
    //     vector<box> boxes = bin->boxes;
    //     vector<point> candidate_points;
    //     for (i=0;i<numOfBox;i++){ //Find all of candidate points for EMS
    //         box box = boxes.at(i);
    //         vector<point> temp = find_points(box);
    //         candidate_points.insert(candidate_points.end(),temp.begin(),temp.end());
    //     }
    //     for (i=0;i<candidate_points.size();i++)
    //         for(j=i+1;j<candidate_points.size();j++);
    //     return candidate_points;
    vector<EMS> *EMSs = bin->EMSs;
    vector<EMS> *new_EMSs = new vector<EMS>();
    for (i=0;i<EMSs->size();i++){
        //EMSs->at(i)
        vector<EMS> temp = diff_process(&EMSs->at(i),box);
        (*new_EMSs).insert(new_EMSs->end(),temp.begin(),temp.end());
    }
    cross_checking_EMS(new_EMSs);
    return new_EMSs;
    
    
    
}
int put_box_into_pin(bin *bin, box *ibox){
    vector<box> *boxes = bin->boxes;
    bin->EMSs = generate_new_EMSs(bin,ibox);
    (*boxes).push_back(*ibox);
    
    
    return 0;
}
void print_point(point *point){
    cout<<" P("<<&point->x<<", "<<&point->y<<", "<<&point->z<<") ";
}
void print_EMS(EMS *EMS){
    print_point(EMS->a);
    print_point(EMS->b);
}
void print_EMSs(vector<EMS> *EMSs){
    int i;
    for (i=0;i<EMSs->size();i++){
        print_EMS(&EMSs->at(i));
    }
}
int main()
{
        bin bin(10,10,10);
        box box1(1,5,5,5,true,new point(0,0,0));
        put_box_into_pin(&bin,&box1);
        box box2(2,2,2,2,true,new point(5,0,0));
        put_box_into_pin(&bin,&box2);
        box box3(3,1,7,7,true,new point(7,0,0));
        put_box_into_pin(&bin,&box3);
    
    
//    EMS *ems = new EMS(new point(0,5,0),new point(10,10,10));
//    box *box2 = new box(2,2,2,2,true,new point(5,0,0));
//    vector<EMS> temp = diff_process(ems,box2);
    
    
    
    
    
    cout<<"FdasfasF";
    return 0;
}









