import math
import random

import matplotlib.cbook as cbook
import matplotlib.patches as patches
import matplotlib.pyplot as plt
import numpy as np

NumOfCity = 30
# listCity = np.random.uniform(1, 100, [NumOfCity, 2])
with cbook.get_sample_data(r'C:\Users\14050\Desktop\TP-AI\Test30.jpg') as image_file:
    image = plt.imread(image_file)
fig, ax = plt.subplots()
ax.imshow(image)
listCity = plt.ginput(NumOfCity)
plt.show()
dicDis = {} # 双点距离字典
for i in range(NumOfCity):
    for j in range(NumOfCity):
        if i > j:
            dis = ((listCity[i][0] - listCity[j][0]) ** 2 +
                   (listCity[i][1] - listCity[j][1]) ** 2) ** 0.5
            dicDis[(i, j)] = dis
            dicDis[(j, i)] = dis
List_Totaldis = []
#LC:形如[0,1,...,30]的解

def Distance(LC):
    # 计算解LC的距离和
    total_dis = dicDis[(LC[-1], LC[0])]
    for i in range(NumOfCity-1):
        total_dis += dicDis[(LC[i], LC[i+1])]
    return total_dis

def Variation(LC):
    # 随机置换两个不同的城市的坐标，变异以产生新解
    p1 = int(random.random() * NumOfCity)
    p2 = int(random.random() * NumOfCity)
    LC[p1],LC[p2] = LC[p2],LC[p1]
    return LC

def SA_TSP():
    # 退火算法
    T0 = 100 * NumOfCity      # 初温
    T1 = 0.001                # 终温
    a = 0.99                  # 温度衰减系数
    iter = 100                # 内循环次数
    # 初始化解（一个随机解）
    Best_LC = np.random.permutation(NumOfCity)
    Best_Totaldis = Distance(Best_LC)
    List_Totaldis.append(Best_Totaldis)
    Start_LC = Best_LC
    Start_Totaldis = Distance(Best_LC)
    Temp_LC = Start_LC
    Temp_Totaldis = Start_Totaldis
    T = T0
    while T >= T1:
        for i in range(iter):
            Temp2_LC = Temp_LC.copy()
            Variation(Temp2_LC)
            delta = Distance(Temp2_LC) - Temp_Totaldis
            if delta < 0:
                Temp_Totaldis = Distance(Temp2_LC)
                Temp_LC = Temp2_LC
                if Temp_Totaldis < Best_Totaldis:
                    Best_Totaldis = Temp_Totaldis
                    Best_LC = Temp_LC.copy()
            elif math.exp(-delta/T) > random.random():
                Temp_Totaldis = Distance(Temp2_LC)
                Temp_LC = Temp2_LC
                Best_Totaldis = Temp_Totaldis
                Best_LC = Temp_LC.copy()
        List_Totaldis.append(Best_Totaldis)
        T = T * a
    return Best_LC, Best_Totaldis, Start_LC, Start_Totaldis

def Draw(City, Best_LC, Best_Totaldis, Start_LC, Start_Totaldis):
    Best_LC = list(Best_LC)
    Best_LC.append(Best_LC[0])
    Best_x = []
    Best_y = []
    for i in Best_LC:
        i = int(i)
        Best_x.append(City[i][0])
        Best_y.append(City[i][1])
    Start_LC = list(Start_LC)
    Start_LC.append(Start_LC[0])
    Start_x = []
    Start_y = []
    for i in Start_LC:
        i = int(i)
        Start_x.append(City[i][0])
        Start_y.append(City[i][1])
    plt.figure(1)
    ax1 = plt.subplot(2, 2, 1)
    ax1.invert_yaxis()
    ax1.plot(Start_x, Start_y, 'r-*')
    plt.title('Start\n'+ 'total_dis = '+str(round(Start_Totaldis, 3)))
    ax2 = plt.subplot(2, 2, 2)
    ax2.invert_yaxis()
    ax2.plot(Best_x, Best_y, 'r-*')
    plt.title('After SA\n'+ 'total_dis = '+str(round(Best_Totaldis, 3)))
    plt.subplot(2, 1, 2)
    plt.plot(range(len(List_Totaldis)), List_Totaldis)
    plt.xlabel('iter')
    plt.ylabel('total_dis')
    fig, ax = plt.subplots()
    ax.imshow(image, origin ='upper')
    plt.plot(Best_x, Best_y, 'r-*')
    plt.show()


def main():
    Best_LC, Best_Totaldis, Start_LC, Start_Totaldis= SA_TSP()
    Draw(listCity, Best_LC, Best_Totaldis, Start_LC, Start_Totaldis)


if __name__ == '__main__':
    main()
