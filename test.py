import cv2 as cv
import numpy as np
from lib.bha_coeficient import bhat_coe
import time
import os
import sys

class test(bhat_coe):
    def __init__(self,frame,model_img,window,n_channel=None,h_v=None,s_v=None,v_v=None,n_bin=None):
        super().__init__(frame,model_img,n_channel,h_v,s_v,v_v,n_bin)
        center = np.concatenate((np.random.randint(0,100,(10,1)),np.random.randint(0,100,(10,1))),axis=1)
        center = np.array([[1,100]])
        self.n_pso = 1
        self.make_window(center,window)
        with open("data.txt","w") as file:
            file.write(str(window))
            file.write(str(self.candidate))

path = "../besave.jpg"
img = cv.imread(path)
cv.imshow("img",img)
window = cv.selectROI(img,fromCenter = None)
cv.destroyWindow("select ROI")
model = img[window[1]:window[1]+window[3],window[0]:window[0]+window[2]]
print("________________________")
my_distance = test(img,model,window,1,[0,180],n_bin = 30)
cv.imshow("roi",model)
cv.waitKey(0)