import numpy as np
import argparse
import math
import scipy
import struct
from scipy import integrate
import cv2  # 利用opencv读取图像
import matplotlib.pyplot as plt 
from PIL import Image
import copy
#w，h is resolution of image，frame_tot is total number of images，file_name is the directory of image
def get_spike(w = 400, h = 250, threshold = 400, frame_tot = 600, file_name = "E:/image/axe"):
    accumulator = np.zeros((h, w))
    byte = 0
    pos = 0
    IE = 1 #暗电流分布期望
    Isigma = 0.008 #暗电流分布方差
    UE = 0#阈值分布期望
    Usigma = 3#阈值分布方差
    CE = 1#电容分布期望
    Csigma = 0.027451#电容分布方差
    #print(struct.pack('??', True, False))
    noise_U = np.random.normal(UE, Usigma, (h, w))
    noise_C = np.random.normal(CE, Csigma, (h, w))
    f = open("E:/image/axe/test.dat", 'wb')
    for i in range(frame_tot):
        print(i)
        num = str(i + 1).zfill(4) #自动补0 总共补成到5位
        img_str = file_name + "/" + num + ".png"
        img = np.array(Image.open(img_str).convert('L').resize((w, h),Image.ANTIALIAS))
        print(img[100][100])
        for a in range(h):
            for b in range(w):
                #print(b)
                #print(img[a][b])
                accumulator[a][b] += img[a][b]
                accumulator[a][b] *= np.random.normal(IE, Isigma, 1)
                if accumulator[a][b] >= (threshold + noise_U[a][b]) * noise_C[a][b]: #np.random.normal(CE, Csigma, 1))
                    accumulator[a][b] = 0
                    byte = byte | (1 << (pos))
                pos += 1
                #print(i)
                if pos == 8:
                    pos = 0
                    temp = struct.pack('B', byte)
                    #print(byte)
                    #print(struct.unpack('B', temp))
                    byte = 0
                    f.write(temp)
        if pos != 0:
            pos = 0
            temp = struct.pack('B', byte)
            byte = 0
            f.write(temp)
    f.close
    return
get_spike()
"""if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("-W", "--width")
    parser.add_argument("-H", "--height")
    parser.add_argument("-phi", "--threshold")
    parser.add_argument("--frame_tot")
    parser.add_argument("--file_name")
    args = parser.parse_args()
    get_spike(args.W, args.H, args.phi, args.frame_tot, args.file_name)
"""
