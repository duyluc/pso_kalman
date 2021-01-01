import cv2 as cv
import numpy as np
import time
import os
import sys
class bhat_coe:
    def __init__(self,frame, model_img, n_channel = 1, h_v = None, s_v = None, v_v = None, n_bin = 180):
        self.model_img = model_img.copy()
        self.frame_shape = frame.shape
        if n_channel < 0:
            print("so channel phai lon hon 0")
            sys.exit()
        if n_channel == 1:
            self.v_range = h_v
            self.channel = [0]
        elif n_channel == 2:
            self.v_range = h_v + s_v
            self.channel = [0,1]
        else:
            self.v_range = h_v + s_v + v_v
            self.channel = [0,1,2]
        self.bin = [n_bin]
        self.preprocess()

    def preprocess(self):
        self.model_hsv = cv.cvtColor(self.model_img,cv.COLOR_BGR2HSV)
        self.model_hst = cv.calcHist(self.model_hsv,self.channel,None,self.bin,self.v_range)
    def make_window(self,pso,window):
        self.candidate = np.ones((self.n_pso,4),dtype = np.uint8)
        self.candidate[:,0:2] = pso - (np.copy(window[2:4])/2)
        self.candidate[:,2:4] = self.candidate[:,2:4]*window[2:4]
        if np.any(self.candidate < 0):
            self.candidate[np.where(self.candidate < 0)] = 0
            print("case 1")
        if np.any(self.candidate[:,0] > self.frame_shape[1]-1):
            self.candidate[np.where(self.candidate[:,0] > self.frame_shape[1]-1),0] = self.frame_shape[1]
            print("case 2")
        if np.any(self.candidate[:,1] > self.frame_shape[0]-1):
            self.candidate[np.where(self.candidate[:,1] > self.frame_shape[0]-1),1] = self.frame_shape[0]
            print("case 3")
    def make_data(self,frame,window):
        pass

