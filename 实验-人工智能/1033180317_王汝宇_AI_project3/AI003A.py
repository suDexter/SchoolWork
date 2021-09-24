start_state = [[1, 5, 3], [2, 4, 6], [7, 0, 8]]  # 初态
end_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]  # 终态
fn_seat = {1: (0, 0), 2: (0, 1), 3: (0, 2), 4: (1, 0), 5: (
    1, 1), 6: (1, 2), 7: (2, 0), 8: (2, 1), 0: (2, 2)}  # 值与位置兑换表


def CalculateHn(src, dest):  # 计算h(n)
    dic, d = fn_seat, 0
    for i in range(len(src)):
        for j in range(len(src[i])):
            pos = dic[src[i][j]]
            y, x = pos[0], pos[1]
            d += abs(y - i) + abs(x - j)
    return d


class Node:  # 边缘队列中的节点类
    state = None  # 状态
    fn = -1  # 启发值
    gn = 0  # 初始状态到当前状态的距离（步数）
    parent = None,  # 父节点
    # 用状态和步数构造节点对象

    def __init__(self, state, gn, parent):
        self.state = state
        self.gn = gn
        self.parent = parent
        # 计算估计距离
        self.fn = CalculateHn(state, end_state) + gn


def CopyState(state):  # 复制状态
    s = []
    for i in state:
        s.append(i[:])
    return s


def GetSpace(state):  # 获取空格的位置
    for y in range(len(state)):
        for x in range(len(state[y])):
            if state[y][x] == 0:
                return y, x


def MoveUp(state):  # 获取空格上移后的状态，不改变原状态
    s = CopyState(state)
    y, x = GetSpace(s)
    s[y][x], s[y - 1][x] = s[y - 1][x], s[y][x]
    return s


def MoveDown(state):  # 获取空格下移后的状态，不改变原状态
    s = CopyState(state)
    y, x = GetSpace(s)
    s[y][x], s[y + 1][x] = s[y + 1][x], s[y][x]
    return s


def MoveLeft(state):  # 获取空格左移后的状态，不改变原状态
    s = CopyState(state)
    y, x = GetSpace(s)
    s[y][x], s[y][x - 1] = s[y][x - 1], s[y][x]
    return s


def MoveRight(state):  # 获取空格右移后的状态，不改变原状态
    s = CopyState(state)
    y, x = GetSpace(s)
    s[y][x], s[y][x + 1] = s[y][x + 1], s[y][x]
    return s


def CalculateHn(src, dest):  # h(n)
    dic, d = fn_seat, 0
    for i in range(len(src)):
        for j in range(len(src[i])):
            pos = dic[src[i][j]]
            y, x = pos[0], pos[1]
            d += abs(y - i) + abs(x - j)
    return d


def GetActions(state):  # 获取指定状态下的操作
    acts = []
    y, x = GetSpace(state)
    if x > 0:
        acts.append(MoveLeft)
    if y > 0:
        acts.append(MoveUp)
    if x < len(state[0]) - 1:
        acts.append(MoveRight)
    if y < len(state[0]) - 1:
        acts.append(MoveDown)
    return acts


def GetMinIndex(open):  # 获取拥有最小启发值的元素索引
    index = 0
    for i in range(len(open)):
        node = open[i]
        if node.fn < open[index].fn:
            index = i
    return index


def StateToFn(state):  # 将状态转换为整数
    fn = 0
    for i in state:
        for j in i:
            fn = fn * 10 + j
    return fn


def AStar(init, goal):  # A*算法寻找初始状态到目标状态的路径
    # 边缘队列初始已有源状态节点
    open = [Node(init, 0, None)]
    closed = {}  # 访问过的状态表
# 队列没有元素则查找失败
    while open:
        # 获取拥有最小估计距离的节点索引
        index = GetMinIndex(open)
        node = open[index]
        closed[StateToFn(node.state)] = True
        if node.state == goal:
            return node
        del open[index]
        # 扩展当前节点
        for act in GetActions(node.state):
            # 获取此操作下到达的状态节点并将其加入边缘队列中
            near = Node(act(node.state), node.gn + 1, node)
            if StateToFn(near.state) not in closed:
                open.append(near)
    return None


def reverse(node):  # 将链表倒序，返回链头和链尾
    if node.parent == None:
        return node, node
    head, rear = reverse(node.parent)
    rear.parent, node.parent = node, None
    return head, node


def main():
    node = AStar(start_state, end_state)
    if node == None:
        print("无法到达")
    else:
        node, rear = reverse(node)
        count = 0
        while node:
            print("第", count, "步：")
            for i in node.state:
                print(i)
            node = node.parent
            count += 1


if __name__ == '__main__':
    main()
