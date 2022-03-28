m=eval(input("请输入体重（kg）："))
h=eval(input("请输入身高（m）："))
B=m/(h*h)
if B<19:
    print("轻体重")
elif B<25:
    print("健康体重")
elif B<28:
    print("超体重")
else:
    print("肥胖")
exit()
