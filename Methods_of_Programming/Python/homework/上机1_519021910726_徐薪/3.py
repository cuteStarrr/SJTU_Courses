n=0
m=0
x=eval(input("Please input the number:"))
while x>0:
    while n<x:
            print(chr(65+(m%26)),' ',end="")
            n=n+1
            m=m+1
    x=x-1
    n=0
    print()
