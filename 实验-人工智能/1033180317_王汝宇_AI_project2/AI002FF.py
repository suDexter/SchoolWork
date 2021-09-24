M = 3
C = 3
K = 2
path = []
paths = []
graph = {}
stateList = []
actions = []


def JudgeAndAddgraph(state):
    lm = state[0]
    lc = state[1]
    lb = state[2]
    if lm < 0 or lc < 0 or M-lm < 0 or C-lc < 0:
        return False
    if (lm < lc and lm != 0) or (M-lm < C-lc and M-lm != 0):
        return False
    if len(stateList) >= 2:
        aim = stateList[-2][:]
        if tuple(aim) in graph.keys() and tuple(state) not in graph[tuple(aim)]:
            graph[tuple(aim)].append(tuple(state))
        else:
            graph[tuple(aim)] = [tuple(state)]
    for p in stateList[:-1]:
        if p[0] == lm and p[1] == lc and p[2] == lb:
            return False

    return True


def Mapping(state):
    lm = state[0]
    lc = state[1]
    lb = state[2]
    if not JudgeAndAddgraph(state):
        return
    if lm == 0 and lc == 0:
        return
    tmp = [0, 0, 0]
    for i in actions:
        tmp[0] = lm - i[0] * lb
        tmp[1] = lc - i[1] * lb
        tmp[2] = -lb
        stateList.append(tmp)
        Mapping(tmp)
        stateList.pop()

    return


def DFS(state):

    if state in path:
        path.append(state)
        return

    if state == (0, 0, -1):
        path.append(state)
        paths.append(path[:])
        return

    path.append(state)

    for i in range(len(graph[state])):
        DFS(graph[state][i])
        path.pop()


def main():
    global actions
    actions = [[1, 0], [0, 1], [1, 1], [2, 0], [0, 2]]
    s = [3, 3, 1]
    act = []
    stateList.append(s)
    Mapping(s)
    DFS(tuple(s))
    num = 0
    for p in paths:
        num += 1
        print("第%d条路径：(lm, lc, lb)" % num)
        print(p[:])
        print("每一步的操作(m, c)")
        for i in range(1, len(p)):
            v = ((p[i-1][0] - p[i][0])*p[i-1][2],(p[i-1][1] - p[i][1])*p[i-1][2])
            act.append(v)
        print(act)
        print("")
        act = []


if __name__ == '__main__':
    main()
