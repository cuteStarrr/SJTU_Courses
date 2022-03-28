from queue import PriorityQueue
import sys
sys.path.append(r"D:\Codes\Code_py")

from AI.MSA.Dynamic_Programming.Pairwise_Alignment import DP_MinCost_Matrix
from AI.MSA.Dynamic_Programming.Three_Sequence_Alignment import ThreeSequenceCost
from AI.MSA.Dynamic_Programming.Pairwise_Alignment import PairCost

# the cost is as follows:
MATCH = 0
MISMATCH = 3
GAP = 2

class Alignment_3D:
    def __init__(self, sx, sy, sz):
        self.sx = sx
        self.sy = sy
        self.sz = sz
        self.lenx = len(sx)
        self.leny = len(sy)
        self.lenz = len(sz)
        self.start = (0, 0, 0)
        self.goal = (self.lenx - 1, self.leny - 1, self.lenz - 1)
        self.cost_matrix_xy = [[0 for i in range(self.lenx)] for i in range(self.leny)]
        self.cost_matrix_yz = [[0 for i in range(self.leny)] for i in range(self.lenz)]
        self.cost_matrix_zx = [[0 for i in range(self.lenz)] for i in range(self.lenx)]
        self.came_from = dict()
        self.cost_so_far = dict()

    def HeuristicMatrix(self):
        self.cost_matrix_xy = DP_MinCost_Matrix(self.sx, self.sy)
        total_cost_xy = self.cost_matrix_xy[self.leny - 1][self.lenx - 1]
        for row in range(len(self.cost_matrix_xy)):
            for line in range(len(self.cost_matrix_xy[row])):
                self.cost_matrix_xy[row][line] = total_cost_xy - self.cost_matrix_xy[row][line]

        self.cost_matrix_yz = DP_MinCost_Matrix(self.sy, self.sz)
        total_cost_yz = self.cost_matrix_yz[self.lenz - 1][self.leny - 1]
        for row in range(len(self.cost_matrix_yz)):
            for line in range(len(self.cost_matrix_yz[row])):
                self.cost_matrix_yz[row][line] = total_cost_yz - self.cost_matrix_yz[row][line]

        self.cost_matrix_zx = DP_MinCost_Matrix(self.sz, self.sx)
        total_cost_zx = self.cost_matrix_zx[self.lenx - 1][self.lenz - 1]
        for row in range(len(self.cost_matrix_zx)):
            for line in range(len(self.cost_matrix_zx[row])):
                self.cost_matrix_zx[row][line] = total_cost_zx - self.cost_matrix_zx[row][line]

    def neighbors(self, current):
        neighbor_list = []
        if current[0] < self.goal[0]:
            neighbor_list.append((current[0] + 1, current[1], current[2]))
        if current[1] < self.goal[1]:
            neighbor_list.append((current[0], current[1] + 1, current[2]))
        if current[2] < self.goal[2]:
            neighbor_list.append((current[0], current[1], current[2] + 1))
        if current[0] < self.goal[0] and current[1] < self.goal[1]:
            neighbor_list.append((current[0] + 1, current[1] + 1, current[2]))
        if current[0] < self.goal[0] and current[2] < self.goal[2]:
            neighbor_list.append((current[0] + 1, current[1], current[2] + 1))
        if current[2] < self.goal[2] and current[1] < self.goal[1]:
            neighbor_list.append((current[0], current[1] + 1, current[2] + 1))
        if current[0] < self.goal[0] and current[1] < self.goal[1] and current[2] < self.goal[2]:
            neighbor_list.append((current[0] + 1, current[1] + 1, current[2] + 1))
        return neighbor_list

    def Cost(self, current, next):
        if next == (current[0] + 1, current[1], current[2]):
            return ThreeSequenceCost(self.sx[next[0]], '-', '-')
        if next == (current[0], current[1] + 1, current[2]):
            return ThreeSequenceCost('-', self.sy[next[1]], '-')
        if next == (current[0], current[1], current[2] + 1):
            return ThreeSequenceCost('-', '-', self.sz[next[2]])
        if next == (current[0] + 1, current[1] + 1, current[2]):
            return ThreeSequenceCost(self.sx[next[0]], self.sy[next[1]], '-')
        if next == (current[0] + 1, current[1], current[2] + 1):
            return ThreeSequenceCost(self.sx[next[0]], '-', self.sz[next[2]])
        if next == (current[0], current[1] + 1, current[2] + 1):
            return ThreeSequenceCost('-', self.sy[next[1]], self.sz[next[2]])
        if next == (current[0] + 1, current[1] + 1, current[2] + 1):
            return ThreeSequenceCost(self.sx[next[0]], self.sy[next[1]], self.sz[next[2]])

    def Heuristic(self, current, goal):
        return abs((goal[0] - current[0]) - (goal[1] - current[1])) * GAP + abs((goal[0] - current[0]) - (goal[2] - current[2])) * GAP + abs((goal[1] - current[1]) - (goal[1] - current[1])) * GAP

        #self.HeuristicMatrix()
        #return self.cost_matrix_xy[current[1]][current[0]] + self.cost_matrix_yz[current[2]][current[1]] + self.cost_matrix_zx[current[0]][current[2]]


    def Astar_ThreeAlignment(self):
        frontier = PriorityQueue()
        frontier.put(self.start, 0)
        self.came_from[self.start] = None
        self.cost_so_far[self.start] = 0

        while not frontier.empty():
            current = frontier.get()

            if current == self.goal:
                return self.cost_so_far[current]
            
            for next in self.neighbors(current):
                new_cost = self.cost_so_far[current] + self.Cost(current, next)
                if next not in self.cost_so_far or new_cost < self.cost_so_far[next]:
                    self.cost_so_far[next] = new_cost
                    priority = new_cost + self.Heuristic(next, self.goal)
                    frontier.put(next, priority)
                    self.came_from[next] = current
    
    def TraceMatch_3D(self):
        self.match_sx = ""
        self.match_sy = ""
        self.match_sz = ""
        current = self.goal
        while current != self.start:
            father = self.came_from[current]
            if father == (current[0] - 1, current[1], current[2]):
                self.match_sx = self.sx[current[0]] + self.match_sx
                self.match_sy = '-' + self.match_sy
                self.match_sz = '-' + self.match_sz
            if father == (current[0], current[1] - 1, current[2]):
                self.match_sx = '-' + self.match_sx
                self.match_sy = self.sy[current[1]] + self.match_sy
                self.match_sz = '-' + self.match_sz
            if father == (current[0], current[1], current[2] - 1):
                self.match_sx = '-' + self.match_sx
                self.match_sy = '-' + self.match_sy
                self.match_sz = self.sz[current[2]] + self.match_sz
            if father == (current[0] - 1, current[1] - 1, current[2]):
                self.match_sx = self.sx[current[0]] + self.match_sx
                self.match_sy = self.sy[current[1]] + self.match_sy
                self.match_sz = '-' + self.match_sz
            if father == (current[0] - 1, current[1], current[2] - 1):
                self.match_sx = self.sx[current[0]] + self.match_sx
                self.match_sy = '-' + self.match_sy
                self.match_sz = self.sz[current[2]] + self.match_sz
            if father == (current[0], current[1] - 1, current[2] - 1):
                self.match_sx = '-' + self.match_sx
                self.match_sy = self.sy[current[1]] + self.match_sy
                self.match_sz = self.sz[current[2]] + self.match_sz
            if father == (current[0] - 1, current[1] - 1, current[2] - 1):
                self.match_sx = self.sx[current[0]] + self.match_sx
                self.match_sy = self.sy[current[1]] + self.match_sy
                self.match_sz = self.sz[current[2]] + self.match_sz
            current = father
        
        print(self.match_sx)
        print(self.match_sy)
        print(self.match_sz)



if __name__ == "__main__":
    sx = 'IPZJJLMLTKJULOSTKTJOGLKJOBLTXGKTPLUWWKOMOYJBGALJUKLGLOSVHWBPGWSLUKOBSOPLOOKUKSARPPJ'
    sy = 'IWTJBGTJGJTWGBJTPKHAXHAGJJSJJPPJAPJHJHJHJHJHJHJHJHJPKSTJJUWXHGPHGALKLPJTPJPGVXPLBJHHJPKWPPDJSG'
    sz = 'IWTJBGTJGJTWGBJTPKHAXHAGJJXJJKPJTPJHJHJHJHJHJHJHJHJHKUTJJUWXHGHHGALKLPJTPJPGVXPLBJHH'
    sx = " " + sx
    sy = " " + sy
    sz = " " + sz
    test = Alignment_3D(sx, sy, sz)
    min_cost = test.Astar_ThreeAlignment()
    print(min_cost)
    test.TraceMatch_3D()