from tkinter import *
from time import sleep
def main():
    r=Tk()
    c=Canvas(r,width=200,height=300,bg='white')
    c.pack()
    ball=c.create_oval(90,10,110,30,fill='red')
    R=10
    h0=280
    v0=0
    t=0.05
    while True:
        h=h0-v0*t
        v=v0+9.8*t
        if h<R:
            h=R
            v=-v0
        c.move(ball,0,h0-h)
        c.update()
        h0=h
        v0=v
        sleep(0.01)


main()
