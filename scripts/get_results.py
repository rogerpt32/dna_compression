import sys
import pandas as pd

if len(sys.argv)!=2:
    exit(-1)

file = sys.argv[1]
size=0
data=[]
isgzip=True
with open(file) as f:
    for line in f.readlines():
        if 'Size' in line:
            size=int(line.replace('Size ','').replace('\n',''))
            row=[size,0,0.0,0,0.0]
        elif 'gzip:' in line:
            isgzip=True
        elif 'our:' in line:
            isgzip=False
        elif 'real\t' in line:
            t=line.replace('real\t','').split('m')
            time=float(t[0])*60+float(t[-1].replace('s\n',''))
            if isgzip:
                row[2]=time
            else:
                row[4]=time
        elif 'compr ' in line:
            compr=int(line.replace('compr ','').replace('\n',''))
            if isgzip:
                row[1]=compr
            else:
                row[3]=compr
                data.append(row)

df=pd.DataFrame(data,columns=['size','gzip_size','gzip_time','paper_size','paper_time'])
df.to_csv('../results/results.csv',index=False)