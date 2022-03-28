place=["zz"]
f=open("excel_ckmx_text.txt",'r',encoding='utf-8')
line=f.readline()
while line:
    line=line.split(',')
    flag=True
    for i in place:
        if line[11]==i:
            flag=False
    if flag:
        place.append(line[11])
    line=f.readline()
place.remove("zz")
print(place)
