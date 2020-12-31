#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <math.h>
#include "SinglePso.h"
#include "Pso.h"
#include "funs.h"
#include "Top.h"
using namespace std;
 
int main()
{
 Srand(time(0)); //random seed
 int amout_ = 400; //number of particles
 float w_ = 0.8; // inertia weight
 // In general, the global acceleration factor c1, historical acceleration factor c2 is equal to (1-w)/2
 float v_scale_ = 0.1; //speed scale factor. Maximum speed and minimum speed range
 int circle_ = 80 ;//Number of iterations
 // This fitness function is two-dimensional. Netizens can change the fitness function according to their needs,
 int in_dims_ = 2; //The dimension of the input coordinates is 2
 float max_in[] = {5.0,5.0}; //upper limit of input parameters
 float min_in[] = {-5.0,-5.0}; //input parameter lower limit
 Pso_Top pso_(amout_,2,0.8,max_in,min_in,v_scale_); //Initial particle swarm object, local top structure particle swarm object
 // Using von Neumann top structure, the number of particles should be even and greater than 12
 //Use four-cluster topology, the number of particles should be a multiple of 4 and greater than 12
 Pso_.set_topFlag(2); //Set top type {0: ring topology; 1: von Neumann topology; 2: four-cluster topology}
    /*
 The above code is the initial method of particle swarm algorithm with local top structure.
 The initialization code of the standard particle swarm algorithm is as follows:
        Pso pso_(amout_,2,0.8,max_in,min_in,v_scale_);
    */
 Pso_.set_w_col(0.99); //Set the inertia attenuation coefficient. Each iteration of the inertia coefficient is multiplied by 0.99. c1 and c2 increase accordingly
 Pso_.set_v_col(0.99); //Set the speed attenuation factor. Upper and lower speed limits. Decay with iteration
 Pso_.gone(circle_); //execution
cout<<"*********Iteration completed********"<<endl;
    cout<<"*****final_gbest   fitness："<<pso_.fitness_gbest_final<<endl;
    cout<<"*****final_gbest   in_：("<<pso_.in_gbest_final[0]<<","<<pso_.in_gbest_final[1]<<")"<<endl;
 cout<<"*********Iteration completed********"<<endl;
}
 
 
 