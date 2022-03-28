from queue import PriorityQueue
import sys
sys.path.append(r"D:\Codes\Code_py")

from AI.MSA.Dynamic_Programming.Pairwise_Alignment import PairCost

# the cost is as follows:
MATCH = 0
MISMATCH = 3
GAP = 2

class Alignment_2D:
    def __init__(self, sx, sy):
        self.sx = sx
        self.sy = sy
        self.lenx = len(sx)
        self.leny = len(sy)
        self.start = (0, 0)
        self.goal = (self.lenx - 1, self.leny - 1)
        self.came_from = dict()
        self.cost_so_far = dict()

    def neighbors(self, current):
        neighbor_list = []
        if current[1] < self.goal[1]:
            neighbor_list.append((current[0], current[1] + 1))
        if current[0] < self.goal[0] and current[1] < self.goal[1]:
            neighbor_list.append((current[0] + 1, current[1] + 1))
        if current[0] < self.goal[0]:
            neighbor_list.append((current[0] + 1, current[1]))
        return neighbor_list

    def Cost(self, current, next):
        if next == (current[0], current[1] + 1):
            return GAP
        if next == (current[0] + 1, current[1]):
            return GAP
        if next == (current[0] + 1, current[1] + 1):
            return PairCost(self.sx[next[0]], self.sy[next[1]])

    def Heuristic(self, current, goal):
        return abs((goal[0] - current[0]) - (goal[1] - current[1])) * GAP

    def TraceMatch_2D(self):
        self.match_sx = ""
        self.match_sy = ""
        current = self.goal
        while current != self.start:
            father = self.came_from[current]
            if father == (current[0], current[1] - 1):
                self.match_sx = "-" + self.match_sx
                self.match_sy = self.sy[current[1]] + self.match_sy
            if father == (current[0] - 1, current[1]):
                self.match_sx = self.sx[current[0]] + self.match_sx
                self.match_sy = "-" + self.match_sy
            if father == (current[0] - 1, current[1] - 1):
                self.match_sx = self.sx[current[0]] + self.match_sx
                self.match_sy = self.sy[current[1]] + self.match_sy
            current = father
        
        print(self.match_sx)
        print(self.match_sy)



    def Astar_Pairwise(self):
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



if __name__ == "__main__":
    sx = "ABCDAACDTGHSSTDFXCVABBHST"
    sy = "BCDAASCTGHSTTDDDCVABBBSS"
    sx = " " + sx
    sy = " " + sy
    test = Alignment_2D(sx, sy)
    min_cost = test.Astar_Pairwise()
    print("the min cost is: ",min_cost)
    test.TraceMatch_2D()
