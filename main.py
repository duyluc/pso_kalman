import cv2 as cv
import numpy as np
import os
import sys
import time
from lib.yolo_lib import yolo
#from lib.pso_lib import pso

weight_path = "yolov4-tiny_last.weights"
label_path = "obj.names"
config_path = "yolov4-tiny.cfg"
video_path = "test_basev4.avi"
def main():
    cap = cv.VideoCapture(video_path)
    my_yolo = yolo(label_path,weight_path,config_path)
    while(1):
        ret,frame = cap.read()
        if not ret:
            print("ngat video")
            break
        frame,_ = my_yolo.run(frame)
        cv.imshow("video",frame)
        if cv.waitKey(20)&0xFF == ord('q'):
            print("break")
            cap.release()
            break

if __name__ == "__main__":
    main()
    cv.destroyAllWindows()
