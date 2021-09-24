import sys


def main():
    with open("tiaojian.txt", "r", encoding='utf-8') as f:
        tiaojian = f.read().splitlines()
    with open("jielun.txt", "r", encoding='utf-8') as f:
        jielun = f.read().splitlines()
    with open("dongwu.txt", "r", encoding='utf-8') as f:
        dongwu = f.read().splitlines()
    for i in range(len(tiaojian)):
        tiaojian[i] = tiaojian[i].split('and')
    shuru = input('输入描述，描述间用,分隔：\n')
    Dshuru = shuru.split(',')
    flag = 0
    sum = 0
    while flag == 0:
        for i in range(len(tiaojian)):
            if set(tiaojian[i]) <= set(Dshuru):
                for j in range(len(tiaojian[i])):
                    Dshuru.remove(tiaojian[i][j])
                Dshuru.append(jielun[i])
                print(Dshuru)
                if set(Dshuru) <= set(dongwu):
                    flag = 1
        sum += 1
        if sum >= 500:
            print("没有这种动物或描述不详细")
            sys.exit(0)
    print("你要找的动物是", Dshuru)


if __name__ == '__main__':
    main()
