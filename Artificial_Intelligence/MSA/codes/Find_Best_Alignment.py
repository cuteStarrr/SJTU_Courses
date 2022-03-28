import os
import sys
sys.path.append(r"D:\Codes\Code_py")
from AI.MSA.Genetic_Algorithm.Genetic_ThreeSequence import ThreeSequence_Population
from AI.MSA.Astar.Astar_Pairwise import Alignment_2D
from AI.MSA.Astar.Astar_ThreeSequence import Alignment_3D
from AI.MSA.Dynamic_Programming.Three_Sequence_Alignment import DP_ThreeCost_Match, DP_ThreeCost_Value
from AI.MSA.Genetic_Algorithm.Genetic_Pairwise import Pairwise_Population
from AI.MSA.Dynamic_Programming.Pairwise_Alignment import DP_GetMatch, DP_MinCost_Value, PairCost
import time


def ReadQuery():
    Pairwise = []
    ThreePair = []
    with open("D:\Codes\Code_py\AI\MSA\MSA_query.txt", 'r') as query:
        query.readline()
        sequence = query.readline()
        while sequence != '3\n':
            Pairwise.append(sequence.replace('\n',''))
            sequence = query.readline()
        sequence = query.readline()
        while sequence != '':
            ThreePair.append(sequence.replace('\n',''))
            sequence = query.readline()
    return Pairwise, ThreePair


def DP_Search_TwoSeq(base):
    min_cost = 999999
    best_match = ''
    with open("D:\Codes\Code_py\AI\MSA\MSA_database.txt", 'r') as database:
        compare = database.readline().replace('\n', '')
        while compare != '':
            cost = DP_MinCost_Value(' ' + base, ' ' + compare)
            if cost < min_cost:
                min_cost = cost
                best_match = compare
            compare = database.readline().replace('\n', '')
    print('\n')
    print('The least cost of pairwise alignment by dynamic programming is: ', min_cost)
    print('The base sequences is: ', base)
    print('The best match is: ', best_match)
    DP_GetMatch(' ' + base, ' ' + best_match)


def Astar_Search_TwoSeq(base):
    min_cost = 999999
    best_match = ''
    with open("D:\Codes\Code_py\AI\MSA\MSA_database.txt", 'r') as database:
        compare = database.readline().replace('\n', '')
        while compare != '':
            test = Alignment_2D(' ' + base, ' ' + compare)
            cost = test.Astar_Pairwise()
            if cost < min_cost:
                min_cost = cost
                best_match = compare
            compare = database.readline().replace('\n', '')
    print('\n')
    print('The least cost of pairwise alignment by Astar Algorithm is: ', min_cost)
    print('The base sequences is: ', base)
    print('The best match is: ', best_match)
    best = Alignment_2D(' ' + base, ' ' + best_match)
    best.Astar_Pairwise()
    best.TraceMatch_2D()


def Genetic_Search_TwoSeq(base):
    min_cost = 999999
    best_match = ''
    best_match_base = ''
    best_match_seq = ''
    with open("D:\Codes\Code_py\AI\MSA\MSA_database.txt", 'r') as database:
        compare = database.readline().replace('\n', '')
        while compare != '':
            test = Pairwise_Population(base, compare)
            cost, match_base, match_seq = test.Best_Solution()
            if cost < min_cost:
                min_cost = cost
                best_match = compare
                best_match_base = match_base
                best_match_seq = match_seq
            compare = database.readline().replace('\n', '')
    print('\n')
    print('The least cost of pairwise alignment by Genetic Algorithm is: ', min_cost)
    print('The base sequences is: ', base)
    print('The best match is: ', best_match)
    print(best_match_base)
    print(best_match_seq)


def DP_Search_ThreeSeq(base):
    min_cost = 999999
    best_match = ''
    with open("D:\Codes\Code_py\AI\MSA\MSA_database.txt", 'r') as database:
        compare = database.readline().replace('\n', '')
        while compare != '':
            cost = DP_ThreeCost_Value(' ' + base[0], ' ' + base[1], ' ' + compare)
            if cost < min_cost:
                min_cost = cost
                best_match = compare
            compare = database.readline().replace('\n', '')
    print('\n')
    print('The least cost of three-sequence alignment by dynamic programming is: ', min_cost)
    print('The base sequences are: ', base)
    print('The best match is: ', best_match)
    DP_ThreeCost_Match(' ' + base[0], ' ' + base[1], ' ' + best_match)


def Astar_Search_ThreeSeq(base):
    min_cost = 999999
    best_match = ''
    with open("D:\Codes\Code_py\AI\MSA\MSA_database.txt", 'r') as database:
        compare = database.readline().replace('\n', '')
        while compare != '':
            test = Alignment_3D(' ' + base[0], ' ' + base[1], ' ' + compare)
            cost = test.Astar_ThreeAlignment()
            if cost < min_cost:
                min_cost = cost
                best_match = compare
            compare = database.readline().replace('\n', '')
    print('\n')
    print('The least cost of three-sequence alignment by Astar Algorithm is: ', min_cost)
    print('The base sequences are: ', base)
    print('The best match is: ', best_match)
    best = Alignment_3D(' ' + base[0], ' ' + base[1], ' ' + best_match)
    best.Astar_ThreeAlignment()
    best.TraceMatch_3D()


def Genetic_Search_ThreeSeq(base):
    min_cost = 999999
    best_match = ''
    best_match_base_one = ''
    best_match_base_two = ''
    best_match_seq = ''
    with open("D:\Codes\Code_py\AI\MSA\MSA_database.txt", 'r') as database:
        compare = database.readline().replace('\n', '')
        while compare != '':
            test = ThreeSequence_Population(base[0], base[1], compare)
            cost, match_base_one, match_base_two, match_seq = test.Best_Solution()
            if cost < min_cost:
                min_cost = cost
                best_match = compare
                best_match_base_one = match_base_one
                best_match_base_two = match_base_two
                best_match_seq = match_seq
            compare = database.readline().replace('\n', '')
    print('\n')
    print('The least cost of three-sequence alignment by Genetic Algorithm is: ', min_cost)
    print('The base sequences are: ', base)
    print('The best match is: ', best_match)
    print(best_match_base_one)
    print(best_match_base_two)
    print(best_match_seq)


def Alignment_Two(pairwise):
    for seq in pairwise:
        start_time = time.time()
        DP_Search_TwoSeq(seq)
        end_time = time.time()
        print("The running time of pairwise alignment by dynamic programming is: %fs" % (end_time - start_time))

        start_time = time.time()
        Astar_Search_TwoSeq(seq)
        end_time = time.time()
        print("The running time of pairwise alignment by A-star algorithm is: %fs" % (end_time - start_time))

        start_time = time.time()
        Genetic_Search_TwoSeq(seq)
        end_time = time.time()
        print("The running time of pairwise alignment by genetic algorithm is: %fs" % (end_time - start_time))


def Alignment_Three(threepair):
    start_time = time.time()
    DP_Search_ThreeSeq(threepair)
    end_time = time.time()
    print("The running time of three-sequence alignment by dynamic programming is: %fs" % (end_time - start_time))

    start_time = time.time()
    Astar_Search_ThreeSeq(threepair)
    end_time = time.time()
    print("The running time of three-sequence alignment by A-star algorithm is: %fs" % (end_time - start_time))

    start_time = time.time()
    Genetic_Search_ThreeSeq(threepair)
    end_time = time.time()
    print("The running time of three-sequence alignment by genetic algorithm is: %fs" % (end_time - start_time))


if __name__ == "__main__":
    Pairwise, ThreePair = ReadQuery() 
    Alignment_Two(Pairwise)
    Alignment_Three(ThreePair)
