#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include<algorithm>
#include "Pso.h"
#include"funs.hpp"
using namespace std;
 
 //Constructor: initialization parameters
Pso::Pso(int swarm_amount_,int in_dim_,float w_,float* max_,float* min_,float v_scale_)
{
    in_gbest_final = new float[in_dim];
    swarm_amount = swarm_amount_;
    fitness_list = new float[swarm_amount];
    in_dim = in_dim_;
    w = w_;
    c1 = (1-w)/2;
    c2 = (1-w)/2;
    min_in = new float[in_dim];
    max_in = new float[in_dim];
    min_v = new float[in_dim];
    max_v = new float[in_dim];
    max_in = max_;
    min_in = min_;
    v_scale = v_scale_;
    for(int i = 0; i<in_dim; i++)
    {
        max_v[i] = (max_[i]-min_[i])*v_scale;
        min_v[i] = -(max_[i]-min_[i])*v_scale;
    }
}
 
 //Set the inertial attenuation coefficient
void Pso::set_w_col(float w_col_)
{
    w_col = w_col_;
}
 
 //Set the attenuation coefficient of the speed range
void Pso::set_v_col(float v_col_)
{
    v_col = v_col_;
}
 
 //Update the particle swarm global optimal solution gbest
void Pso::gbest(int init_flag)
{
 Float* in_gbest_temp = new float[in_dim]; //Store the optimal particle coordinates for each round
 Float fitness_gbest_temp; //Optimal fitness value for each round
    get_min(swarm_amount,vector_pso,in_gbest_temp,&fitness_gbest_temp,in_dim);
    for(int i=0; i<swarm_amount; i++)
    {
 //If it is in the first iteration, or fitness_gbest_temp is better than the particle gbest
 //Replace gbest of particles with fitness_gbest_temp and in_gbest_temp
        if (init_flag == 0 ||fitness_gbest_temp < vector_pso[i].fitness_gbest)
        {
            vector_pso[i].get_gbest(in_gbest_temp,fitness_gbest_temp);
        }
    }
}
 
//Initialize the particle swarm's coordinates, speed, historical best, global best
void Pso::initialize()
{
    for(int i=0; i<swarm_amount; i++)
    {
        Pso_single single(in_dim,max_in,min_in,max_v,min_v,w,c1,c2);
        single.init_();
        single.get_fitness();
        single.init_pbest();
        vector_pso.push_back(single);
    }
    gbest(0);
}
 
 //Update the speed, coordinates, historical best and global best of the particle swarm
void Pso::update()
{
    if (w_col != 1.0)
    {
 W = w*w_col; //decay w
 C1 = (1-w)/2; //increase c1
 C2 = (1-w)/2; //add c2
    }
    if (v_col != 1.0)
    {
 V_scale = v_scale * v_col; //decay v_scale
    }
    for(int i=0; i<swarm_amount; i++)
    {
        vector_pso[i].updata_v();
        vector_pso[i].updata_in();
        vector_pso[i].get_fitness();
        vector_pso[i].updata_pbest();
    }
    gbest(1);
}
 
 //Initialize, and repeat circle_round iterations
void Pso::gone(int circle_)
{
    this->initialize();
    for (int i = 0; i<circle_; i++)
    {
        if (i%5 == 0)
        {
 Cout<<""""<<i<<"iteration"<<endl;
        }
        this->update();
    }
 //Get_final_gbest: calculate the final optimal particle
    get_final_gbest(swarm_amount,vector_pso,in_gbest_final,&fitness_gbest_final,in_dim);
}
 
 
 