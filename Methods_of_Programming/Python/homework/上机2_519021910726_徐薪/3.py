def maxandmin(n,flag):#若flag=1，则是求最大值，若flag=0，则是求最小值
    c=n%10
    b=int(n/10)%10
    a=int(n/100)
    if a<b:
        tmp=a
        a=b
        b=tmp
    if b<c:
        tmp=b
        b=c
        c=tmp
    if a<b:
        tmp=a
        a=b
        b=tmp
    if flag==1:
        return 100*a+10*b+c
    else:
        return 100*c+10*b+a

def out_come(n):
    front=maxandmin(n,1)
    behind=maxandmin(n,0)
    old=front-behind
    print(front,'-',behind,'=',old)
    return old
    

def main():
    new=eval(input("Please input n:"))
    old=0
    while old!=new:
        old=out_come(new)
        new=out_come(old)



main()
