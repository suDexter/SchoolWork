import numpy as np

MaxPlayer, MinPlayer = 'X', 'O'


def isMovesLeft(board):  # False = 棋盘满了
    for i in range(3):
        for j in range(3):
            if (board[i][j] == '_'):
                return True
    return False


def evaluate(b):  # 给棋盘估值
    for row in range(3):
        if (b[row][0] == b[row][1] and b[row][1] == b[row][2]):
            if (b[row][0] == MaxPlayer):
                return 10
            elif (b[row][0] == MinPlayer):
                return -10
    for col in range(3):
        if (b[0][col] == b[1][col] and b[1][col] == b[2][col]):
            if (b[0][col] == MaxPlayer):
                return 10
            elif (b[0][col] == MinPlayer):
                return -10
    if (b[0][0] == b[1][1] and b[1][1] == b[2][2]):
        if (b[0][0] == MaxPlayer):
            return 10
        elif (b[0][0] == MinPlayer):
            return -10
    if (b[0][2] == b[1][1] and b[1][1] == b[2][0]):
        if (b[0][2] == MaxPlayer):
            return 10
        elif (b[0][2] == MinPlayer):
            return -10
    return 0

def minimax(board, depth, isMaxPlayer):
    score = evaluate(board)
    if (score == 10):
        return score
    if (score == -10):
        return score
    if (isMovesLeft(board) == False):
        return 0
    if (isMaxPlayer):
        best = -1000
        for i in range(3):
            for j in range(3):
                if (board[i][j] == '_'):
                    board[i][j] = MaxPlayer
                    best = max(best, minimax(board, depth + 1, not isMaxPlayer))
                    board[i][j] = '_'
        return best
    else:
        best = 1000
        for i in range(3):
            for j in range(3):
                if (board[i][j] == '_'):
                    board[i][j] = MinPlayer
                    best = min(best, minimax(board, depth + 1, not isMaxPlayer))
                    board[i][j] = '_'
        return best


def findBestMove(board):
    bestVal = -1000
    bestMove = (-1, -1)
    # 计算全空格的moveVal，算出并返回bestVal和对应的bestMove
    for i in range(3):
        for j in range(3):
            if (board[i][j] == '_'):
                board[i][j] = MaxPlayer
                moveVal = minimax(board, 0, False)  # 移动的价值(10/-10/0)
                board[i][j] = '_'
                if (moveVal > bestVal):
                    bestMove = (i, j)
                    bestVal = moveVal
    return bestMove


def printBoard(board):
    matrix = np.mat(board)  # 列表转矩阵
    print(matrix)

def rolling(board):
    while (1):
        printBoard(board)
        if (evaluate(board) == 10):
            print("结束！")
            break
        if (evaluate(board) == -10):
            print("结束！")
            break
        if (isMovesLeft(board) == False):
            print("和棋！")
            break
        print("输入你的走棋坐标，两数之间用空格隔开")
        print("左上端点记为0 0")
        x, y = map(int, input().split())
        if board[x][y] != '_':
            print("非法输入")
            continue
        board[x][y] = MinPlayer
        bestMove = findBestMove(board)
        board[bestMove[0]][bestMove[1]] = MaxPlayer

def main():
    board = [
            ['_', '_', '_'],
            ['_', '_', '_'],
            ['_', '_', '_']
    ]
    boardA = [
            ['_', '_', '_'],
            ['_', 'X', '_'],
            ['_', '_', '_']
    ]
    boardB = [
            ['_', '_', '_'],
            ['_', 'O', '_'],
            ['_', '_', '_']
    ]
    print("Human first?[Y/N]")
    chooseA = input()
    print("you choose X or O?")
    chooseB = input()
    if chooseA == 'Y' and chooseB == 'O':
        rolling(board)
    elif chooseA == 'Y' and chooseB == 'X':
        global MaxPlayer, MinPlayer
        MaxPlayer, MinPlayer = 'O', 'X'
        rolling(board)
    elif chooseA == 'N' and chooseB == 'O':
        rolling(boardA)
    elif chooseA == 'N' and chooseB == 'X':
        MaxPlayer, MinPlayer = 'O', 'X'
        rolling(boardB)
    else:
        print("输入有误！")


if __name__ == '__main__':
    main()
