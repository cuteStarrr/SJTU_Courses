# the cost is as follows:
MATCH = 0
MISMATCH = 3
GAP = 2

def PairCost(sx, sy):
    if sx == sy:
        return MATCH
    elif sx == "-":
        return GAP
    elif sy == "-":
        return GAP
    else:
        return MISMATCH

def DP_MinCost_Value(sx, sy):
    lenx = len(sx) # 横向的序列
    leny = len(sy) # 竖向的序列
    cost_old = [0] * leny
    cost_new = [0] * leny
    for row in range(leny):
        cost_old[row] = row * GAP
    for line in range(1, lenx):
        cost_new[0] = line * GAP
        for row in range(1, leny):
            cost_new[row] = min([PairCost(sx[line], sy[row]) + cost_old[row - 1], GAP + cost_new[row - 1], GAP + cost_old[row]])
        for row in range(leny):
            cost_old[row] = cost_new[row]
    return cost_new[leny - 1]

def DP_GetMatch(sx, sy):
    cost_matrix = DP_MinCost_Matrix(sx, sy)
    lenx = len(sx) # 横向的序列
    leny = len(sy) # 竖向的序列
    row = leny - 1
    line = lenx - 1
    sx_matched = ""
    sy_matched = ""
    while not(row == 0 and line == 0):
        cost_list = [PairCost(sx[line], sy[row]) + cost_matrix[row - 1][line - 1], GAP + cost_matrix[row - 1][line], GAP + cost_matrix[row][line - 1]]
        pos = cost_list.index(cost_matrix[row][line])
        if pos == 0:
            sx_matched = sx[line] + sx_matched
            sy_matched = sy[row] + sy_matched
            row -= 1
            line -= 1
        elif pos == 1:
            sx_matched = "-" + sx_matched
            sy_matched = sy[row] + sy_matched
            row -= 1
        else:
            sx_matched = sx[line] + sx_matched
            sy_matched = "-" + sy_matched
            line -= 1
    print(sx_matched)
    print(sy_matched)
    return cost_matrix[leny - 1][lenx - 1]
    

def DP_MinCost_Matrix(sx, sy):
    lenx = len(sx) # 横向的序列
    leny = len(sy) # 竖向的序列
    cost_matrix = [[0 for i in range(lenx)] for i in range(leny)]
    for row in range(leny):
        cost_matrix[row][0] = row * GAP
    for line in range(1, lenx):
        cost_matrix[0][line] = line * GAP
        for row in range(1, leny):
            cost_matrix[row][line] = min([PairCost(sx[line], sy[row]) + cost_matrix[row - 1][line - 1], GAP + cost_matrix[row - 1][line], GAP + cost_matrix[row][line - 1]])
    return cost_matrix


if __name__ == "__main__":
    sx = "ABCD"
    sy = "BCD"
    sx = " " + sx
    sy = " " + sy
    min_cost = DP_MinCost_Value(sx,sy)
    print("min cost: ", min_cost)
    