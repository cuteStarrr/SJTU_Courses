from tkinter import *
w=Tk()
c=Canvas(w,width=520,height=420,bg='white')
c.pack()
    
def drawPicture(x1,y1,m1,x2,y2,m2,k,n):
    c.create_line(x1,y1,x2,y2)
    c.create_text(x1,y1,text=round(m1,2),anchor=S)
    if k==n:
        c.create_text(x2,y2,text=round(m2,2),anchor=S)

def drawPoint(a,i,n):
    maxmoney=a*((1+i)**n)
    dy=maxmoney/380
    dx=500/n
    m1=a*(1+i)
    x1=500/(2*n)
    y1=420-m1/dy
    for k in range(2,n+1):
        m2=a*((1+i)**k)
        x2=x1+dx
        y2=420-m2/dy
        drawPicture(x1,y1,m1,x2,y2,m2,k,n)
        x1=x2
        y1=y2
        m1=m2
    
def main():
    m=eval(input("Please input the money:"))
    r=eval(input("Please input the rate:"))
    y=eval(input("Please input the year:"))
    drawPoint(m,r,y)

main()
