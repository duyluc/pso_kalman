#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>
#include "SinglePso.h"
#include "funs.hpp"
 
#define PI 3.1415926
 
using namespace std;
 
 //Generate random numbers between 0 and 1
float random_single()
{
    return ((float)(rand()%1000))/1000.0;
}
 
 //Generate a random array with dimension dims
float* random_array(int dims,float *max_,float *min_)
{
    float *temp = new float[dims];
    for(int i=0; i<dims; i++)
 
    {
        float random_ = random_single();
        temp[i] = (max_[i] - min_[i])*random_ + min_[i];
    }
    return temp;
}
 
 //fitness_fun: fitness function uses "Rastrigin's function"
float fitness_fun(float* inin)
{
    float x1 = inin[0];
    float x2 = inin[1];
    float rastrigin_ = 20 + pow(x1,2) + pow(x2,2) - 10*(cos(2*PI*x1) + cos(2*PI*x2));
    return rastrigin_;
}
 
 //Array copy
void copy_(float src[],float dst[],int dims)
{
    for(int i = 0; i<dims; i++)
    {
        dst[i] = src[i];
    }
}
 
 // Through calculation, get the minimum fitness value and corresponding coordinates in the vector
void get_min(int mount,vector<Pso_single> temp_pso,float* min_in,float* min_fit,int in_dims_)
{
    for(int i=0; i<mount; i++)
    {
        if(i == 0 || temp_pso[i].fitness_ < *min_fit)
        {
            *min_fit = temp_pso[i].fitness_;
            copy_(temp_pso[i].in_,min_in,in_dims_);
 
        }
    }
}
 
 //Through calculation, the final optimal solution is obtained
void get_final_gbest(int mount,vector<Pso_single> temp_pso,float* final_in,float* final_fit,int in_dims_)
{
    for(int i=0; i<mount; i++)
    {
        if(i == 0 || temp_pso[i].fitness_ < *final_fit)
        {
            *final_fit = temp_pso[i].fitness_gbest;
            copy_(temp_pso[i].in_,final_in,in_dims_);
        }
    }
}
 
 