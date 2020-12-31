#ifndef FUNS_HPP_INCLUDED
#define FUNS_HPP_INCLUDED
#include <vector>
#include "SinglePso.h"
 
using namespace std;
 
 //random_single: Generate floating point numbers of 0-1
float random_single();
 
 //random_array: randomly generate an array of dims dimensions
float* random_array(int dims,float *max_, float *min_);
 
 //fitness_fun: function to generate fitness value
float fitness_fun(float* in_);
 
 //copy_: array deep copy
void copy_(float src[],float dst[],int dims);
 
 //get_max: Through calculation, get the particle with the smallest fitness value
void get_min(int mount,vector<Pso_single> temp_pso,float* max_in,float* max_fit,int in_dims_);
 
 //get_max: Through calculation, get the particle with the smallest fitness value
void get_final_gbest(int mount,vector<Pso_single> temp_pso,float* final_in,float* final_fit,int in_dims_);
 
#endif // FUNS_HPP_INCLUDED