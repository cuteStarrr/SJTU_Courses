from tkinter import *

def DrawaPicture(p):
    r=Tk()
    c=Canvas(r,width=450,height=180,bg='white')
    c.pack()
    name=list(("edu","noedu","white","black","men","women"))
    for i in range(0,11,2):
        All=c.create_rectangle(60+30*i,60,90+30*i,160,outline='black',fill='green')
        money=int(p[i]*100/(p[i]+p[i+1]))
        nomoney=100-money
        M=c.create_rectangle(60+30*i,60,90+30*i,60+money,outline='black',fill='red')
        c.create_text(75+30*i,60,text=money/100,anchor=S)
        c.create_text(75+30*i,160,text=nomoney/100,anchor=S)
        c.create_text(75+30*i,160,text=name[int(i/2)],anchor=N)
    c.create_rectangle(10,5,20,15,outline='black',fill='red')
    c.create_text(25,10,text="rich",anchor=W)
    c.create_rectangle(10,20,20,30,outline='black',fill='green')
    c.create_text(25,25,text="poor",anchor=W)

def ReadLine(f,p):
    line=f.readline()
    while line:
        flag=False
        num=0
        n=len(line)
        if line[n-6]=='>':
            flag=True
        for i in range(0,n):
            if line[i]==',':
                num=num+1
            if num==3:
                if line[i+1]=='B' or line[i+1]=='M' or line[i+1]=='D':
                    if flag:
                        p[0]=p[0]+1    #有学位有钱的人
                    else:
                        p[1]=p[1]+1    #有学问没钱的人
                else:
                    if flag:
                        p[2]=p[2]+1    #没学位有钱的人
                    else:
                        p[3]=p[3]+1    #没学位没钱的人
            elif num==8:
                if line[i+1]=='W':
                    if flag:
                        p[4]=p[4]+1    #白的有钱的人
                    else:
                        p[5]=p[5]+1    #白的没钱的人
                else:
                    if flag:
                        p[6]=p[6]+1    #其他颜色有钱的
                    else:
                        p[7]=p[7]+1    #其他颜色没钱的
            elif num==9:
                if line[i+1]=='M':
                    if flag:
                        p[8]=p[8]+1    #男人有钱的
                    else:
                        p[9]=p[9]+1    #男人没钱的
                else:
                    if flag:
                        p[10]=p[10]+1  #女人有钱的
                    else:
                        p[11]=p[11]+1  #女人没钱的
        line=f.readline()


def main():
    f=open("data.txt",'r')
    people=list((0,0,0,0,0,0,0,0,0,0,0,0))
    ReadLine(f,people)
    DrawaPicture(people)


main()
