import numpy as np

def sigmoid(x,deriv=False):
    if(deriv==True):
        return x*(1-x)
    return 1/(1+np.exp(-x))

def GO(X, Y):
    syn0 = np.random.random((2,20))
    syn1 = np.random.random((20,1))
    for i in range(60000):
        l0 = X
        l1 = sigmoid(np.dot(l0,syn0))
        l2 = sigmoid(np.dot(l1,syn1))
        l2_error = Y - l2
        l2_delta = l2_error*sigmoid(l2,deriv=True)
        l1_error = l2_delta.dot(syn1.T)
        l1_delta = l1_error * sigmoid(l1,deriv=True)
        syn1 += l1.T.dot(l2_delta)
        syn0 += l0.T.dot(l1_delta)
    print("输入层各点权重：")
    print(syn0)
    print("隐藏层各点权重：")
    print(syn1)

if __name__ == '__main__':
    trainData = np.loadtxt('TrainingData.csv', dtype=float,
                           delimiter=',', usecols=(0, 1))
    trainLabel = (np.loadtxt('TrainingData.csv', dtype=float,
                             delimiter=',', usecols=2)).reshape(trainData.shape[0], 1)
    testData = np.loadtxt('TestingData.csv', dtype=float,
                          delimiter=',', usecols=(0, 1))
    testLabel = (np.loadtxt('Tes.csv',
                            dtype=float, delimiter=',', usecols=2)).reshape(testData.shape[0], 1)
    GO(trainData, trainLabel)
