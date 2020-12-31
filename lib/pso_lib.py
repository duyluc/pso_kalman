import cv2 as cv
import numpy as np
import time
import os
import sys

class pso:
    def __int__(self,in_dim v_lim, p_lim, w, c1, c2, n_pop):
        self.v_lim = v_lim
        self.p_lim = p_lim
        self.w = w
        self.c1 = c1
        self.c2 = c2
        self.in_dim = in_dim
        self.n_pop = n_pop
    def update_pbest(self, n_pbest):
        self.pbest = np.copy(n_pbest)
    def update_gbest(self,n_gbest):
        self.gbest = np.copy(n_gbest)
    def update_v(self):
        self.v = self.w*self.v + self.c1*np.multiply(self.pbest-self.pso) + self.c2*np.multiply(self.gbest-self.pso)
    def update_pso(self):
        self.pso = self.pso + self.v
    def c_fitness(self):
        
    def init_pbest(self, in_pbest):
        self.pbest = np.copy(in_pbest)
    def init_gbest(self):
        self.gbest = np.copy(in_gbest)
    def init_pso(self, in_pso):
        self.pso = np.copy(in_psoc)
    def get_position(self):
        return self.pso

