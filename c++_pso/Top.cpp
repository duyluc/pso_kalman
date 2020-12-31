#include <iostream>
//#include <stdlib.h>
#include <vector>
#include <cmath>
#include <time.h>
//#include<algorithm>
#include "Top.h"
#include"funs.hpp"
 
using namespace std;
 
 
void Pso_Top::set_topFlag(int topFlag)
{
    top_flag = topFlag;
}
 
 /*top_index_0: In a ring-shaped top structure, each particle shares information about the particles before and after it
 top_index_1: In the von Neumann top structure, each particle shares information about the particles before and after it
 top_index_2: Four-cluster structure, which divides all particles into 4 clusters. The particles in the cluster share information; some particles share information with other clusters
 //index acquisition of ring top structure
void top_index_0(int i_ ,int size_v,int* index_v)
{
    index_v[0] = (i_+size_v-1)%size_v;
    index_v[1] = i_;
    index_v[2] = (i_+1)%size_v;
}
 //The built-in function of get_row_col:top_index_1.
 //Function: reasonable allocation of rows and columns, the values ​​of rows and columns should be as close as possible
int get_row_col(int num_)
{
    int row = 0;
    for(int i=1; i<=sqrt(num_); i++)
    {
        if (num_%i==0)
        {
            row = i;
        }
    }
    return row;
}
 //The built-in function of get_index:top_index_1.
 //Function: Get the index of the front, back, left and right of the target particle.
 //(i,j) = (-1,0) before
 //(i,j) = (1,0) after
 //(i,j) = (0,-1) left
 //(i,j) = (0,1) right
int get_index(int row,int col,int row_curr,int col_curr,int i,int j)
{
    return ((row_curr+i+row)%row)*col + ((col_curr+j+col)%col);
}
 //index acquisition of Von Neumann structure
void top_index_1(int i_ ,int size_v,int* index_v)
{
    int row,col,row_curr,col_curr;
    row = get_row_col(size_v);
    col = size_v/row;
    row_curr = i_/col;
    col_curr = i_%col;
 index_v[0] = get_index(row,col,row_curr,col_curr,-1,0);// 
 index_v[1] = get_index(row,col,row_curr,col_curr,1,0);//Up
 index_v[2] = i_;//middle
 index_v[3] = get_index(row,col,row_curr,col_curr,0,-1);//Left
 index_v[4] = get_index(row,col,row_curr,col_curr,0,11);;//right
}
 //Four-cluster structure: divide all particles into 4 clusters, the particles in the cluster share information; some particles share information with other cluster
int top_index_2(int group_id ,int swarm_id)
{
    /*
 Note: In the following, group-i-k is used to denote the number k of the i-th cluster; for example, group-1-0 means the particle number 0 of the first cluster;
Array of group_index_0 means: the 0th, 1st and 2nd particles in group-0 are respectively group-1-0, group-2-1,
 Group-3-2 is connected; group_index_1, group_index_2, group_index_3 and so on.
    */
    int  group_index_0[3][2] = {{1,0},{2,1},{3,2}};
    int  group_index_1[3][2] = {{0,0},{3,1},{2,0}};
    int  group_index_2[3][2] = {{1,2},{0,1},{3,0}};
    int  group_index_3[3][2] = {{2,2},{1,1},{0,2}};
    switch(group_id)
    {
    case 0:
        return group_index_0[swarm_id][0]*4 + group_index_0[swarm_id][1];
        break;
    case 1:
        return group_index_1[swarm_id][0]*4 + group_index_0[swarm_id][1];
        break;
    case 2:
        return group_index_2[swarm_id][0]*4 + group_index_0[swarm_id][1];
        break;
    case 3:
        return group_index_3[swarm_id][0]*4 + group_index_0[swarm_id][1];
        break;
    };
}
 
 
void Pso_Top::gbest(int init_flag)
{
    float* in_gbest_temp = new float[in_dim];
    float fitness_gbest_temp;
    int* index_;
    if (top_flag < 2)
    {
 // top_flag = 0: ring structure
 // top_flag = 1: Von Neumann structure
        for(int i=0; i<swarm_amount; i++)
        {
 //For loop: used to calculate the global optimal solution gbest of each particle under the current top model
            switch(top_flag)
            {
            case 0:
 index_ = new int[3]; //The index of each particle and the particles that share information with it
 _ Top_index_0(i ,swarm_amount,index_); //The index value is complex
                break;
            case 1:
 index_ = new int[5];//The index of each particle and the particles that share information with it
 Top_index_1(i ,swarm_amount,index_);//The index value is complex
                break;
            }
 vector<Pso_single> vector_local; //Define a container to store particles that share information with the current particle
            for(int j = 0; j<sizeof(index_); j++)
            {
 vector_local[j] = vector_pso[index_[j]];//Particles of shared information are stored one by one
            }
  //Particles to obtain the optimal fitness value
            get_min(vector_local.size(),vector_local,in_gbest_temp,&fitness_gbest_temp,in_dim);
 // //Update particle gbest
 // // init_flag == 0, it means the first round of iteration
            if (init_flag == 0||fitness_gbest_temp<vector_pso[i].fitness_gbest)
            {
                vector_pso[i].get_gbest(in_gbest_temp,fitness_gbest_temp);
            }
        }
    }
    else
    {
 //Top_flag = 2: four cluster structure
 //The following for loop: loop 4 times to calculate the gbest of the particles in each cluster separately
        for(int i=0; i<4; i++)
        {
 Int sub_amout = int(swarm_amount/4);//sub_amout: number of particles in each sub-cluster
 vector<Pso_single> vector_local; //define a container to store each cluster particle group
            for(int j = 0; j<sub_amout; j++)
            {
 vector_local[j] = vector_pso[index_[i*sub_amout+j]];//store all particles in the current cluster
            }
 
 // //get_min: calculate the gbest in the current sub-cluster
            get_min(vector_local.size(),vector_local,in_gbest_temp,&fitness_gbest_temp,in_dim);
            for(int j=0; j<sub_amout; j++)
            {
 // // Assign gbest to all particles in the current cluster
                if (init_flag == 0||fitness_gbest_temp<vector_pso[i].fitness_gbest)
                {
                    vector_pso[i*sub_amout+j].fitness_gbest = fitness_gbest_temp;
                    vector_pso[i*sub_amout+j].in_gbest = in_gbest_temp;
                }
                if(j<3)
                {
 // If j<3: the first three particles, we must compare the gbest of the particles connected to the outer cluster
                    int index_ = top_index_2(i ,j);
                    if (fitness_gbest_temp<vector_pso[i].fitness_gbest)
                    {
                        vector_pso[i*sub_amout+j].fitness_gbest = vector_pso[index_].fitness_;
                        vector_pso[i*sub_amout+j].in_gbest = vector_pso[index_].in_;
                    }
                }
            }
        }
    }
}
 
 
 
 