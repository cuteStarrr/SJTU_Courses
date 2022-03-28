import math
x=eval(input("Please input the number:"))
m=math.sin(x)**2+math.cos(x)
a=(m+1)**3-3*m
b=4*m-1
if x>0:
    print("The output is:",a)
elif x<0:
    print("The output is:",b)
else:
    print("The output is:",math.pi)
