def DeleteOld(l,num):
    n=len(l)-1
    for i in range(num,l[n]+1,num):
        if i in l:
            l.remove(i)
    return l

def Isnum(num):
    for i in range(2,num):
        if num%i==0:
            return False
    return True

def FindandDelete(s):
    while s:
        if Isnum(s[0]):
            print(s[0])
        s=DeleteOld(s,s[0])
    print("End")

def CreateList():
    n=eval(input("Please input the number:"))
    s=list(range(2,n+1))
    return s

def main():
    aList=CreateList()
    FindandDelete(aList)

main()
