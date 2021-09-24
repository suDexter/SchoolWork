import json
import random
import os
import itertools

seq = list(itertools.permutations([0,1,2,3,4,5,6,7],8)) #全排列
with open('seq.json', 'w') as file_object:
    json.dump(seq, file_object)

def calculate_fitness(s): #计算适应度 =（28-互相攻击的皇后对的数目）
    num = 28
    for i in range(len(s)):
        for j in range(i + 1,len(s)):
            if s[i] == s[j]:
                num -= 1
            offset = j - i
            if abs(s[i] - s[j]) == offset:
                num -= 1
    return num

def selection(populations, percents): #选择（轮盘赌）
    temp = 0
    for i in range(len(populations)):
        temp += percents[i]
        percents[i] = temp
    percents.insert(0, 0)
    new_populations = []
    for i in range(len(populations)):
        a = random.random()
        for pos in range(len(populations)):
            if percents[pos] <= a < percents[pos + 1]:
                new_populations.append(populations[pos])
                break
    return new_populations

def crossover(populations, pcrossover): #交叉（从正中间隔断交叉）
    temp1 = []
    temp2 = []
    new_populations = []
    n = int(len(populations)*pcrossover)
    temp_pop = []
    for i in range(n):
        tmp = random.choice(populations)
        temp_pop.append(tmp)
        populations.remove(tmp)
    for i in range(n):
        tmp = random.choice(temp_pop)
        temp_pop.remove(tmp)
        if i < n / 2:
            temp1.append(tmp)
            continue
        temp2.append(tmp)
    temp1 = temp1 + temp2
    temp2 = temp1[::-1]
    for i in range(n):
        new_populations.append(temp1[i][:4] + temp2[i][4:])
    for item in populations:
        new_populations.append(item)
    return new_populations

def mutation(populations, pmutation):#变异（数组中随机位置换随机一个数）
    n = int(len(populations)*pmutation)
    temp_pop = []
    for i in range(n):
        tmp = random.choice(populations)
        temp_pop.append(tmp)
        populations.remove(tmp)
    for item in temp_pop:
        a = random.randint(0,7)
        b = random.randint(0,7)
        item[a] = b
    for item in temp_pop:
        populations.append(item)
    return populations

populations = []
n = 100  # 种群规模
iterations = 500 #最大迭代次数
pcrossover = 0.5 #交叉率
pmutation = 0.05 #变异率
output = [0,0,0,0,0,0,0,0]
with open('seq.json', 'r') as file_object:
    seqs = json.load(file_object)
for i in range(n):
    tmp = random.choice(seqs)
    populations.append(tmp)
print('取初代种群' + str(len(populations)) + '个')
for iteration in range(iterations + 1):
    fitness = []
    for item in populations:
        a = calculate_fitness(item)
        fitness.append(a)
        if a == 28:
            print(item)
            for i in range(0,8):
                output[item[i]] = 8
                print(output)
                output = [0,0,0,0,0,0,0,0]
            os.system("pause")
    print(str(iteration)+'代没有满足条件的个体')
    sum_of_fitness = sum(fitness)
    percents = [float(fitness[i]/sum_of_fitness) for i in range(len(fitness))]
    populations = mutation(crossover(selection(populations, percents), pcrossover), pmutation)