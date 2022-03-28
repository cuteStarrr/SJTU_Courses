from math import ceil
from random import random, randint
import sys
sys.path.append(r"D:\Codes\Code_py")

from AI.MSA.Dynamic_Programming.Pairwise_Alignment import DP_MinCost_Matrix
from AI.MSA.Dynamic_Programming.Three_Sequence_Alignment import ThreeSequenceCost
from AI.MSA.Dynamic_Programming.Pairwise_Alignment import PairCost

# the cost is as follows:
MATCH = 0
MISMATCH = 3
GAP = 2

class ThreeSequence_Population:
    def __init__(self, sx, sy, sz):
        self.sx = sx # string
        self.sy = sy
        self.sz = sz
        self.population = 20 # The population of pairwise genetic algorithm
        self.r_sp = 0.2 # the length of sequence increasing
        self.seq_len = ceil(max(len(self.sx), len(self.sy), len(self.sz)) * (1 + self.r_sp))
        self.generations = 500 # the times of reproduce
        self.cross_rate = 0.6
        self.mutation_rate = 0.4
        # to get the group: the form of group is [ [ [sx_block], [sy_block] , [sz_block]], [ [sx_block], [sy_block] , [sz_block]], ... ]
        self.group = []
        for i in range(self.population):
            self.group.append(self.RandomStart())
        # to get the fitness of each individual
        self.group_fitness = [] # fitness is the cost of alignment, the less the better
        for i in range(self.population):
            self.group_fitness.append(self.Individual_Fitness(self.group[i]))
        #self.best_fitness = min(self.group_fitness) # the least fitness(cost)


    def RandomStart(self):
        group = []
        block = []
        for j in range(self.seq_len - len(self.sx)):
            block_pos = randint(0, self.seq_len - 1)
            while block_pos in block:
                block_pos = randint(0, self.seq_len - 1)
            block.append(block_pos)
        block.sort()
        group.append(block)

        sx = list(self.sx)
        sy = list(self.sy)
        sz = list(self.sz)
        for b in block:
            sx.insert(b, '-')
        block = []
        t = self.seq_len - len(self.sy)
        for i in range(self.seq_len):
            if sy[i] != sx[i] and t > 0:
                sy.insert(i, '-')
                block.append(i)
                t -= 1
            if t == 0:
                break
        group.append(block)
        block = []
        t = self.seq_len - len(self.sz)
        for i in range(self.seq_len):
            if sz[i] != sy[i] and t > 0:
                sz.insert(i, '-')
                block.append(i)
                t -= 1
            if t == 0:
                break
        group.append(block)
        return group

        group = []
        times = [self.seq_len - len(self.sx), self.seq_len - len(self.sy), self.seq_len - len(self.sz)]
        for i in range(3):
            block = []
            for j in range(times[i]):
                block_pos = randint(0, self.seq_len - 1)
                while block_pos in block:
                    block_pos = randint(0, self.seq_len - 1)
                block.append(block_pos)
            block.sort()
            group.append(block)

        return group


    # suppose one condition:
    # ABCDAA-CDTGHSSTDFXCVABBHST----
    # -BCDAASC-TGHSTTDDDCVABBBSS----
    # first insert '-' to sequence and calculate pairwise cost
    def Individual_Fitness(self, individual):
        sx_block = individual[0]
        sy_block = individual[1]
        sz_block = individual[2]
        sx = list(self.sx)
        sy = list(self.sy)
        sz = list(self.sz)

        for block in sx_block:
            sx.insert(block, '-')
        for block in sy_block:
            sy.insert(block, '-')
        for block in sz_block:
            sz.insert(block, '-')

        fitness = 0
        for i in range(self.seq_len):
            fitness += ThreeSequenceCost(sx[i], sy[i], sz[i])
        
        return fitness


    def CrossoverRange(self, father_block, mother_block):
        point = 1

        count_left_father = sum(i < point for i in father_block)
        count_left_mother = sum(i < point for i in mother_block)
        while count_left_father != count_left_mother or count_left_father == 0:
            point +=1
            count_left_father = sum(i < point for i in father_block)
            count_left_mother = sum(i < point for i in mother_block)

        return point


    def Crossover(self, sx, sy):
        x = sx
        y = sy
        for i in range(3):
            point = self.CrossoverRange(x[i], y[i])
            pos = 0
            while x[i][pos] < point:
                tmp = x[i][pos]
                x[i][pos] = y[i][pos]
                y[i][pos] = tmp
                pos += 1
                if pos == len(x[i]):
                    break
            x[i].sort()
            y[i].sort()
        

    def Mutation(self, individual):
        for seq in range(3):
            for i in range(len(individual[seq])): # for every block
                if random() < self.mutation_rate: # mutate
                    new_block = randint(0, self.seq_len - 1)
                    while new_block in individual[seq]:
                        new_block = randint(0, self.seq_len - 1)
                    individual[seq][i] = new_block

            individual[seq].sort()


    def Reproduce(self):
        for i in range(ceil(self.population * self.cross_rate)):
            # select two individuals at random
            father = randint(0, len(self.group) - 1)
            mother = randint(0, len(self.group) - 1)
            while father == mother:
                mother = randint(0, len(self.group) - 1)

            x = self.group[father] # individual
            y = self.group[mother]
            
            # crossover these two individuals
            self.Crossover(x, y)

            # mutation
            self.Mutation(x)
            self.Mutation(y)

            self.group.append(x)
            self.group.append(y)

            self.group_fitness.append(self.Individual_Fitness(x))
            self.group_fitness.append(self.Individual_Fitness(y))



    def Survive(self):
        fitness_sort = sorted(self.group_fitness, key = int, reverse = False)
        fitness_sort = fitness_sort[0: self.population] # in increase order
        group = []
        for fit in fitness_sort:
            group.append(self.group[self.group_fitness.index(fit)])
        
        self.group = group
        self.group_fitness = fitness_sort
        

    def Evolution(self):
        generation = 0
        while generation < self.generations:
            generation += 1
            self.Reproduce()
            self.Survive()

        return self.group_fitness[0]

    
    def Best_Solution(self):
        min_cost = self.Evolution()
        best_individual = self.group[0]
        
        sx = list(self.sx)
        sy = list(self.sy)
        sz = list(self.sz)

        for block in best_individual[0]:
            sx.insert(block, '-')
        for block in best_individual[1]:
            sy.insert(block, '-')
        for block in best_individual[2]:
            sz.insert(block, '-')

        return min_cost, ''.join(sx), ''.join(sy), ''.join(sz)


if __name__ == "__main__":
    sx = "ABCDAACDTGHSSTDFXCVABBHST"
    sy = "BCDAASCTGHSTTDDDCVABBBSS"
    sz = "FGSAACDGGTTDDDCVABBASSS"
    test = ThreeSequence_Population(sx, sy, sz)
    print(test.Best_Solution())