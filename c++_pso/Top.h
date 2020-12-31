#ifndef TOP_H_INCLUDED
#define TOP_H_INCLUDED
#include <iostream>
#include <vector>
#include "Pso.h"
using namespace std;
 
/*
Pso_Top :
 It is a subclass of Pso and implements the function of a local top structure.
*/
 
class Pso_Top : public Pso
{
private:
 int top_flag = 0; //Topology value label
public:
 //Pso_Top: Constructor
    Pso_Top(int swarm_amount_,int in_dim_,float w_,float* max_,float* min_,float v_scale_):Pso(swarm_amount_,in_dim_,w_,max_,min_,v_scale_)
    {
    }
 //Set_topFlag: set top type
    void set_topFlag(int topFlag);
 //Gbest: generate global optimal
    void gbest(int init_flag);
};
#endif // TOP_H_INCLUDED
 
 