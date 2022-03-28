def issquare(n):
    for i in range(10,32):
        if i*i==n:
            return True
    return False


def istwosame(n):
    n=str(n)
    if n[0]==n[1] or n[0]==n[2] or n[1]==n[2]:
        return True
    else:
        return False


def main():
    n=eval(input("Please input n:"))
    num=0
    for i in range(100,n+1):
        if issquare(i) and istwosame(i):
            print(i,end=' ')
            num=num+1
    print('\n')
    print("The number is:",num)



main()
