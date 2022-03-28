import sys
sys.path.append(r"D:\Codes\Code_py\AI\MSA\Dynamic_Programming")
# the cost is as follows:
MATCH = 0
MISMATCH = 3
GAP = 2

from Pairwise_Alignment import PairCost


def ThreeSequenceCost(c1, c2, c3):
    return PairCost(c1, c2) + PairCost(c1, c3) + PairCost(c2, c3)

def DP_ThreeCost_Value(si,sj,sk):
    leni = len(si)
    lenj = len(sj)
    lenk = len(sk)
    cost_matrix = [[[0 for i in range(lenk)] for j in range(lenj)] for k in range(leni)]

    for i in range(leni):
        cost_matrix[i][0][0] = i * GAP * 2
    for j in range(lenj):
        cost_matrix[0][j][0] = j * GAP * 2
    for k in range(lenk):
        cost_matrix[0][0][k] = k * GAP * 2
    
    for i in range(1, leni):
        for j in range(1, lenj):
            cost_matrix[i][j][0] = min(ThreeSequenceCost(si[i], sj[j], "-") + cost_matrix[i - 1][j - 1][0], ThreeSequenceCost(si[i], "-", "-") + cost_matrix[i - 1][j][0], ThreeSequenceCost("-", sj[j], "-") + cost_matrix[i][j - 1][0])
    for i in range(1, leni):
        for k in range(1, lenk):
            cost_matrix[i][0][k] = min(ThreeSequenceCost(si[i], "-", sk[k]) + cost_matrix[i - 1][0][k - 1], ThreeSequenceCost(si[i], "-", "-") + cost_matrix[i - 1][0][k], ThreeSequenceCost("-", "-", sk[k]) + cost_matrix[i][0][k - 1])
    for k in range(1, lenk):
        for j in range(1, lenj):
            cost_matrix[0][j][k] = min(ThreeSequenceCost("-", sj[j], sk[k]) + cost_matrix[0][j - 1][k - 1], ThreeSequenceCost("-", "-", sk[k]) + cost_matrix[0][j][k - 1], ThreeSequenceCost("-", sj[j], "-") + cost_matrix[0][j - 1][k])
    
    for i in range(1, leni):
        for j in range(1, lenj):
            for k in range(1, lenk):
                cost_matrix[i][j][k] = min([cost_matrix[i - 1][j - 1][k - 1] + ThreeSequenceCost(si[i],sj[j],sk[k]), \
                    cost_matrix[i - 1][j][k - 1] + ThreeSequenceCost(si[i], "-", sk[k]), \
                        cost_matrix[i][j - 1][k - 1] + ThreeSequenceCost("-", sj[j], sk[k]), \
                            cost_matrix[i - 1][j - 1][k] + ThreeSequenceCost(si[i], sj[j], "-"), \
                                cost_matrix[i][j][k - 1] + ThreeSequenceCost("-", "-", sk[k]), \
                                    cost_matrix[i][j - 1][k] + ThreeSequenceCost("-", sj[j], "-"), \
                                        cost_matrix[i - 1][j][k] + ThreeSequenceCost(si[i], "-", "-")])
    
    return cost_matrix[leni - 1][lenj - 1][lenk - 1] 

def DP_ThreeCost_Match(si,sj,sk):
    leni = len(si)
    lenj = len(sj)
    lenk = len(sk)
    cost_matrix = [[[0 for i in range(lenk)] for j in range(lenj)] for k in range(leni)]

    for i in range(leni):
        cost_matrix[i][0][0] = i * GAP * 2
    for j in range(lenj):
        cost_matrix[0][j][0] = j * GAP * 2
    for k in range(lenk):
        cost_matrix[0][0][k] = k * GAP * 2
    
    for i in range(1, leni):
        for j in range(1, lenj):
            cost_matrix[i][j][0] = min(ThreeSequenceCost(si[i], sj[j], "-") + cost_matrix[i - 1][j - 1][0], ThreeSequenceCost(si[i], "-", "-") + cost_matrix[i - 1][j][0], ThreeSequenceCost("-", sj[j], "-") + cost_matrix[i][j - 1][0])
    for i in range(1, leni):
        for k in range(1, lenk):
            cost_matrix[i][0][k] = min(ThreeSequenceCost(si[i], "-", sk[k]) + cost_matrix[i - 1][0][k - 1], ThreeSequenceCost(si[i], "-", "-") + cost_matrix[i - 1][0][k], ThreeSequenceCost("-", "-", sk[k]) + cost_matrix[i][0][k - 1])
    for k in range(1, lenk):
        for j in range(1, lenj):
            cost_matrix[0][j][k] = min(ThreeSequenceCost("-", sj[j], sk[k]) + cost_matrix[0][j - 1][k - 1], ThreeSequenceCost("-", "-", sk[k]) + cost_matrix[0][j][k - 1], ThreeSequenceCost("-", sj[j], "-") + cost_matrix[0][j - 1][k])
    
    for i in range(1, leni):
        for j in range(1, lenj):
            for k in range(1, lenk):
                cost_matrix[i][j][k] = min([cost_matrix[i - 1][j - 1][k - 1] + ThreeSequenceCost(si[i],sj[j],sk[k]), \
                    cost_matrix[i - 1][j][k - 1] + ThreeSequenceCost(si[i], "-", sk[k]), \
                        cost_matrix[i][j - 1][k - 1] + ThreeSequenceCost("-", sj[j], sk[k]), \
                            cost_matrix[i - 1][j - 1][k] + ThreeSequenceCost(si[i], sj[j], "-"), \
                                cost_matrix[i][j][k - 1] + ThreeSequenceCost("-", "-", sk[k]), \
                                    cost_matrix[i][j - 1][k] + ThreeSequenceCost("-", sj[j], "-"), \
                                        cost_matrix[i - 1][j][k] + ThreeSequenceCost(si[i], "-", "-")])
    
    i = leni - 1
    j = lenj - 1
    k = lenk - 1
    si_matched = ""
    sj_matched = ""
    sk_matched = ""
    while not(i == 0 and j == 0 and k == 0):
        cost_list = [cost_matrix[i - 1][j - 1][k - 1] + ThreeSequenceCost(si[i],sj[j],sk[k]), \
                    cost_matrix[i - 1][j][k - 1] + ThreeSequenceCost(si[i], "-", sk[k]), \
                        cost_matrix[i][j - 1][k - 1] + ThreeSequenceCost("-", sj[j], sk[k]), \
                            cost_matrix[i - 1][j - 1][k] + ThreeSequenceCost(si[i], sj[j], "-"), \
                                cost_matrix[i][j][k - 1] + ThreeSequenceCost("-", "-", sk[k]), \
                                    cost_matrix[i][j - 1][k] + ThreeSequenceCost("-", sj[j], "-"), \
                                        cost_matrix[i - 1][j][k] + ThreeSequenceCost(si[i], "-", "-")]
        pos = cost_list.index(cost_matrix[i][j][k])
        if pos == 0:
            si_matched = si[i] + si_matched
            sj_matched = sj[j] + sj_matched
            sk_matched = sk[k] + sk_matched
            i -= 1
            j -= 1
            k -= 1
        elif pos == 1:
            si_matched = si[i] + si_matched
            sj_matched = "-" + sj_matched
            sk_matched = sk[k] + sk_matched
            i -= 1
            k -= 1
        elif pos == 2:
            si_matched = "-" + si_matched
            sj_matched = sj[j] + sj_matched
            sk_matched = sk[k] + sk_matched
            j -= 1
            k -= 1
        elif pos == 3:
            si_matched = si[i] + si_matched
            sj_matched = sj[j] + sj_matched
            sk_matched = "-" + sk_matched
            i -= 1
            j -= 1
        elif pos == 4:
            si_matched = "-" + si_matched
            sj_matched = "-" + sj_matched
            sk_matched = sk[k] + sk_matched
            k -= 1
        elif pos == 5:
            si_matched = "-" + si_matched
            sj_matched = sj[j] + sj_matched
            sk_matched = "-" + sk_matched
            j -= 1
        elif pos == 6:
            si_matched = si[i] + si_matched
            sj_matched = "-" + sj_matched
            sk_matched = "-" + sk_matched
            i -= 1
    print(si_matched)
    print(sj_matched)
    print(sk_matched)
    return cost_matrix[leni - 1][lenj - 1][lenk - 1]

if __name__ == "__main__":
    sx = 'IPZJJLMLTKJULOSTKTJOGLKJOBLTXGKTPLUWWKOMOYJBGALJUKLGLOSVHWBPGWSLUKOBSOPLOOKUKSARPPJ'
    sy = 'IWTJBGTJGJTWGBJTPKHAXHAGJJSJJPPJAPJHJHJHJHJHJHJHJHJPKSTJJUWXHGPHGALKLPJTPJPGVXPLBJHHJPKWPPDJSG'
    sz = 'IWTJBGTJGJTWGBJTPKHAXHAGJJXJJKPJTPJHJHJHJHJHJHJHJHJHKUTJJUWXHGHHGALKLPJTPJPGVXPLBJHH'
    sx = " " + sx
    sy = " " + sy
    sz = " " + sz
    min_cost = DP_ThreeCost_Match(sx, sy, sz)
    print("min cost: ", min_cost)



