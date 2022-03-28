def slope(p1,p2):
    if(p1[0]==p2[0]):
        return "The slope doesn't exist!"
    else:
        return (p1[1]-p2[1])/(p1[0]-p2[0])

def intercept(p1,p2):
    if(p1[0]==p2[0]):
        return "No intercept!"
    else:
        k=slope(p1,p2)
        return p1[1]-k*p1[0]

p1=eval(input("Please input the first point:"))
p2=eval(input("Please input the second point:"))
print("The slope is :",slope(p1,p2))
print("The intercept is :",intercept(p1,p2))
