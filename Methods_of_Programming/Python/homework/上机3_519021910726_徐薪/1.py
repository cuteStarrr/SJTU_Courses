def numOfLeap(year):
    num=0
    for i in range(2000,year):
        if(i%4==0 and i%100!=0)or(i%400==0):
            num=num+1
    return num

def dayOfYear(year,month,day):
    num=0
    monthday=[31,28,31,30,31,30,31,31,30,31,30,31]
    if(year%4==0 and year%100!=0)or(year%400==0):
        monthday[1]=29
    for i in range(month-1):
        num=num+monthday[i]
    num=num+day
    return num

def ifAndPrint(n):
    num=n%5
    if(num>0 and num<4):
        print("Shoot fish!")
    else:
        print("Dry net!")

def main():
    year=eval(input("Please input the final year:"))
    month=eval(input("Please input the final month:"))
    day=eval(input("Please input the final day:"))
    numleap=numOfLeap(year)
    numday=dayOfYear(year,month,day)
    n=numleap+numday
    ifAndPrint(n)


main()
