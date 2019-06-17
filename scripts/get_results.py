import sys
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import rcParams

rcParams['font.family'] = 'serif'
rcParams['font.size'] = 10
rcParams['font.sans-serif'] = ['Console Modern']
rcParams['savefig.format'] = ['pdf']
rcParams['savefig.bbox'] = 'tight'
rcParams['savefig.pad_inches'] = 0


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

df['gzip_percent'] = 100*df['gzip_size']/df['size']
df['paper_percent'] = 100*df['paper_size']/df['size']

fig, ax = plt.subplots()
ax.set_xscale('log', basex=2)
plt.ylim(-5,125)
plt.xlabel('Size (B)')
plt.ylabel('Compression level (%)')
ax.plot(df['size'],df['gzip_percent'],label='gzip')
ax.plot(df['size'],df['paper_percent'],label='paper')
plt.legend()
plt.tight_layout()
fig.savefig("../plots/compression.pdf")
#plt.show()
plt.cla()
plt.clf()
plt.close()

fig, ax = plt.subplots()
ax.set_xscale('log', basex=2)
plt.xlabel('Size (B)')
plt.ylabel('Time (s)')
ax.plot(df['size'],df['gzip_time'],label='gzip')
ax.plot(df['size'],df['paper_time'],label='paper')
plt.legend()
plt.tight_layout()
fig.savefig("../plots/time.pdf")
#plt.show()
plt.cla()
plt.clf()
plt.close()