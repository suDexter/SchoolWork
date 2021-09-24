import numpy as np

def KNN(testdata, trainData, trainLabel, K):
    datanum = trainData.shape[0]
    testData = np.tile(testdata, (datanum, 1))
    disData = np.sqrt(np.sum((testData - trainData)**2, axis=1))
    disRank = np.argsort(disData)
    labelCount = {}
    for i in range(K):
        k_label = trainLabel[disRank[i]][0]
        labelCount[k_label] = labelCount.get(k_label, 0)
    testLabel = sorted(labelCount.items(), key=lambda item: item[1], reverse=True)  # 降序排序
    return testLabel[0][0]

def CalculateRatio(result, testLabel):
    num = 0
    for i in range(len(result)):
        if(result[i] == testLabel[i]):
            num = num + 1
    return num/len(result)

if __name__ == '__main__':
    result = []
    trainData = np.loadtxt('iris-data-training.csv', dtype=float,delimiter=',', usecols=(0, 1, 2, 3))
    trainLabel = (np.loadtxt('iris-data-training.csv', dtype=str, delimiter=',', usecols=4)).reshape(trainData.shape[0], 1)
    testData = np.loadtxt('iris-data-testing.csv', dtype=float,delimiter=',', usecols=(0, 1, 2, 3))
    testLabel = (np.loadtxt('iris-data-testing.csv', dtype=str, delimiter=',', usecols=4))
    for i in range(testData.shape[0]): #行数
        testdata = testData[i]
        testlabel = KNN(testdata, trainData, trainLabel, 10)
        result.append(testlabel)
    print(result)
    print("正确率为" + str(CalculateRatio(result, testLabel)) + "%")
