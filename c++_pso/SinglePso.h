#ifndef SINGLEPSO_H_INCLUDED
#define SINGLEPSO_H_INCLUDED
/*
 Pso_single: a class that encapsulates a single particle;
 Data members of this class, including particles:
 Coordinate dimension: in_dims, coordinates, adaptation value, upper and lower limits of position, upper and lower limits of speed, inertia coefficient,
 Global speed factor, local speed factor, upper and lower speed limits, speed range factor, local optimal solution, global optimal solution,
 Methods: Random initialization, calculating fitness value, updating global optimal, updating local optimal
*/
class Pso_single
{
private:
 int in_dims; //coordinate dimension
 float *in_max, *in_min; //upper and lower limit of position
 float *v_max,*v_min; //upper and lower speed limit
 float w, c1, c2; //inertia coefficient, local speed factor, global speed factor
public:
 float *v_; //speed
 float fitness_; //The fitness value of particles
 float *in_; //Coordinates of particles
 float fitness_pbest; //The historical optimal fitness value of particles
 float *in_pbest; //The historical optimal coordinates of particles
 float fitness_gbest; //Global optimal fitness value of particles
 float *in_gbest; //Global optimal coordinates of particles
 
 //Pso_single: constructor
Pso_single(int in_dims_,float *inmax, float *inmin, float *vmax, float *vmin,float w_,float c1_,float c2_);
 //Init_: randomly initialize the velocity and position of particles
void init_();
 //Get_fitness: calculate the fitness value of the current coordinates
void get_fitness();
 //Init_pbest: Initialization history is optimal
void init_pbest();
 //Updata_pbest: update history is optimal
void updata_pbest();
 //Get_gbest: update the global optimal
void get_gbest(float *in_gbest_,float fitness_gbest_);
 //Updata_v:: update speed
void updata_v();
 //Updata_in: update coordinates
void updata_in();
};
 
#endif // SINGLEPSO_H_INCLUDED
 
 