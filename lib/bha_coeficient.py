import cv2 as cv
import numpy as np
import time
import os
import sys
class bhat_coe:
    

    def __init__(self, model_img, n_channel = 1, h_v = None, s_v = None, v_v = None, n_bin):
        if n_channel < 0:
            print("so channel phai lon hon 0")
            sys.exit()
        if n_channel == 1:
            self.v_range = h_v
            self.channel = [0]
        if n_channel == 2:
            self.v_range = h_v + s_v
            self.channal = [0,1]
        else:
            self.v_range = h_v + s_v + v_v
            self.channal = [0,1,2]
        self.bin = n_bin
        preprocess()

    def preprocess(self):
        self.model_hsv = cv.cvtColor(self.model_img,cv.COLOR_BGR_HSV)
        self.model_hst = cv.calcHist(model_hsv,self.channal,None,self.bin,self.v_range)
    def make_window(self,pso,window):
        self.candidate = np.ones((self.n_pso,4),dtype = np.uint8)
        self.candidate[:,0:2] = pso - window[2:4]
        self.candidate[:,2:4] = self
    def make_data(self,frame,window):

