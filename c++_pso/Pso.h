#ifndef PSO_H_INCLUDED
#define PSO_H_INCLUDED
#include "SinglePso.h"
#include <vector>
using namespace std;
/*
 Pso class: standard particle swarm optimization
 Members: Multiple Single_pso, speed factor, inertia factor, etc.
*/
class Pso
{
protected:
 int swarm_amount; //number of particle swarms
 int in_dim; //Dimension of particle coordinates
    float w,c1,c2;  //
    float* max_in;  //
    float* min_in;  //
    float* max_v;   //
    float* min_v;   //
    float* fitness_list; //
 float v_scale = 0.1; //speed range factor. Recommended 0.05<v_scale<0.2
 float w_col = 1.0; // inertial attenuation factor, recommended 0.96<w_col<1.0
 float v_col = 1.0; //Speed ​​attenuation factor, recommended 0.96<v_col<1.0
 Vector<Pso_single> vector_pso; //container for storing all particles

public:
 float* in_gbest_final; //store the final optimal coordinates
 float fitness_gbest_final; //Optimal fitness value corresponding to optimal coordinates
 //Pso: constructor
    Pso(int swarm_amount_,int in_dim_,float w_,float* max_,float* min_,float v_scale_);
 //Set_w_col: Set the inertial attenuation factor
    void set_w_col(float w_col);
 //Set_v_col: Set speed attenuation factor
    void set_v_col(float v_col);
 //Gbest: calculate the global optimal gbest
    void gbest(int flag);
 //Initialize: Initialize the coordinate value, velocity, adaptation value, local optimal, global optimal, of each particle,
    void initialize();
 //Update: update coordinate value, speed, adaptation value, local optimal, global optimal,
    void update();
 //Gone: loop iteration. circle_ indicates the number of iterations
    void gone(int circle_);
};
 
 
#endif // PSO_H_INCLUDED
 
 