#include <iostream>
#include<algorithm>
#include"SinglePso.h"
#include"funs.h"
 
using namespace std;
 
 
Pso_single::Pso_single(int in_dims_,float *inmax, float *inmin, float *vmax, float *vmin,float w_,float c1_,float c2_)
{
  in_dims = in_dims_; //coordinate dimension
  fitness_ = 0.0; //fit value of particles
  in_ = new float [in_dims]; //coordinates of particles
  v_ = new float [in_dims]; //speed
  fitness_pbest = 0.0; //historical optimal fitness value of particles
  in_pbest = new float [in_dims]; //The historical optimal coordinates of the particle
  fitness_gbest = 0.0; //Global optimal fitness value of particles
  in_gbest = new float [in_dims]; //Global optimal coordinates of particles
  in_max = inmax; //Maximum position
  in_min = inmin; //Lower limit of position
  v_max = vmax; //Maximum speed
  v_min = vmin; //lower speed limit
  w = w_; //coefficient of inertia,
  c1 = c1_; // historical speed factor
  c2 = c2_; //Global speed factor
}
 
void Pso_single::init_()
{ // // Random initialization of coordinates
  in_ = random_array(in_dims,in_max,in_min);
 /// Random initialization speed
  v_ = random_array(in_dims,v_max,v_min);
}
 
void Pso_single::get_fitness()
{
  //Calculate the fitness value
  fitness_ = fitness_fun(in_);
}
 
void Pso_single::init_pbest()
{
// Copy the coordinate value and adaptation value directly
  copy_(in_,in_pbest,in_dims);
  fitness_pbest = fitness_;
}
 
void Pso_single::updata_pbest()
{
  //if the current fitness value of the particle is greater than the historical optimal value pbest, re-copy
if(fitness_<=fitness_pbest){
copy_(in_,in_pbest,in_dims);
fitness_pbest = fitness_;
}
 
void Pso_single::get_gbest(float *in_gbest_,float fitness_gbest_)
{ //The incoming global optimal is assigned to the global optimal of the current particle
// ** //Global optimal needs to compare the fitness value of all particles,
 // //So compare all the particles externally first. Then come in again.
copy_(in_gbest_,in_gbest,in_dims);
fitness_gbest = fitness_gbest_;
}
 
void Pso_single::updata_v(){
 //// Update speed according to the following formula
//v=v*w + (pbestin-in)*c1 + (gbestin-in)*c2
 The speed must not exceed the upper and lower limits
for(int i = 0;i<in_dims;i++){
v_[i] = v_[i]*w + (in_pbest[i] - in_[i])*c1 + (in_gbest[i] - in_[i])*c2;
if(v_[i]>v_max[i])
{v_[i] = v_max[i];}
if (v_[i]<v_min[i])
{v_[i] = v_min[i];}
}
}
 
void Pso_single::updata_in(){
 // Update the location. The position must not exceed the upper and lower limits
for(int i = 0;i<in_dims;i++){
in_[i] = in_[i] + v_[i];
if (in_[i]>in_max[i])
{in_[i] = in_max[i];}
  if (in_[i]<in_min[i])
  {in_[i] = in_min[i];}
}
}
 