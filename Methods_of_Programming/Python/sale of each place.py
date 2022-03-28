import matplotlib.pyplot as plt

def CreateTheMap(p):
    fig=plt.figure()
    fig,axes=plt.subplots(nrows=2,ncols=3)
    axes[0,0].set(title=p+"2016年销售图")
    axes[0,1].set(title=p+"2017年销售图")
    axes[0,2].set(title=p+"2018年销售图")
    axes[1,0].set(title=p+"2019年销售图")
    axes[1,1].set(title=p+"2020年销售图")
    axes[1,2].set(title=p+"2016年到2019年销售汇总图")
    plt.show()
    return fig,axes



def DrawPicture(s,p,m,x):
    amount=[]
    for k in range(1,len(s)):
        amount.append(s[k])
    num=s[0]-2016
    if num<3:
        xz=0
        yz=num
    else:
        xz=1
        yz=num%3
    x[xz,yz].plot(range(13),s)



    

place=['京津冀', '成都', '福州', '广州', '杭州', '合肥', '济南', '云贵', '西北', '绵阳', '南昌', '南宁', '无锡', '武汉', '长春', '长沙', '郑州', '重庆', '南京', '太原', '乌鲁木齐']
file=open("excel_ckmx_text.txt",'r',encoding='utf-8')
year=[2016,2017,2018,2019,2020]
sale=[0,0,0,0,0,0,0,0,0,0,0,0,0]
for i in place:
    drawmap,xy=CreateTheMap(i)
    for j in year:
        sale[0]=j
        file.seek(0)
        line=file.readline()
        while line:
            line=line.split(',')
            if line[11]==i:
                date=line[1].split('-')
                if int(date[0])==j:
                    number=int(date[1])
                    sale[number]=sale[number]+1
            line=file.readline()
        print(i,sale)
        DrawPicture(sale,i,drawmap,xy)
        for m in range(len(sale)):
            sale[m]=0
