def f(a,n):
    if n>1:
        return 10*f(a,n-1)+a
    else:
        return a


def main():
    a=eval(input("Please input a:"))
    n=eval(input("Please input n:"))
    s=0
    for i in range(1,n+1):
        s=s+f(a,i)
    print("The answer is:",s)



main()
