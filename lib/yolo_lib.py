import cv2 as cv
import numpy as np
import os
import sys
import time
np.random.seed(42)

class yolo:
	def __init__(self, label_path, weight_path, config_path):
		self.label_path = label_path
		self.weight_path = weight_path
		self.config_path = config_path
		self.LABELS = open(self.label_path).read().strip().split("\n")
		self.COLORS = np.random.randint(0, 255, size=(len(self.LABELS), 3),dtype="uint8")
		self.net = cv.dnn.readNetFromDarknet(self.config_path, self.weight_path)
	def run(self,frame):
		self.frame = frame.copy()
		(H, W) = self.frame.shape[:2]
		ln = self.net.getLayerNames()
		ln = [ln[i[0] - 1] for i in self.net.getUnconnectedOutLayers()]
		blob = cv.dnn.blobFromImage(self.frame, 1 / 255.0, (416, 416),swapRB=True, crop=False)
		self.net.setInput(blob)
		layerOutputs = self.net.forward(ln)
		end = time.time()
		boxes = []
		yolo_box = []
		confidences = []
		classIDs = []
		for output in layerOutputs:
			for detection in output:
				scores = detection[5:]
				classID = np.argmax(scores)
				confidence = scores[classID]
				if confidence > 0.3:
					box = detection[0:4] * np.array([W, H, W, H])
					(centerX, centerY, width, height) = box.astype("int")
					x = int(centerX - (width / 2))
					y = int(centerY - (height / 2))
					boxes.append([x, y, int(width), int(height)])
					confidences.append(float(confidence))
					classIDs.append(classID)
					#print(classID)
		idxs = cv.dnn.NMSBoxes(boxes, confidences, 0.5,0.3)
		if len(idxs) > 0:
			for i in idxs.flatten():
				(x, y) = (boxes[i][0], boxes[i][1])
				(w, h) = (boxes[i][2], boxes[i][3])
				color = [int(c) for c in self.COLORS[classIDs[i]]]
				cv.rectangle(self.frame, (x, y), (x + w, y + h), (255,0,0), 2)
				yolo_box = np.append(yolo_box,[boxes[i]])
				text = "{}: {:.4f}".format(self.LABELS[classIDs[i]], confidences[i])
				cv.putText(self.frame, text, (int(x+w/2),int(y+h/2)), cv.FONT_HERSHEY_SIMPLEX,0.5, color, 2)
		try:
			yolo_box = yolo_box.reshape(len(idxs),-1)
		except Exception:
			print('ok')
		return self.frame,yolo_box
