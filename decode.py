import os.path
from os import path
import codecs
directory = 'results/gui/ThreadedTests/'
results = os.listdir(directory)
#for file in results:
#    file = open(file=directory+file,'r',encoding='utf-16')
#    content = file.read()
#    file.close()
#    file = open(file=str(directory)+str(file),'w',encoding='utf-8')
#    file.write(content)
#    file.close()

path1 = "results/gui/seqTest/i101_times.txt"
path2 = "results/gui/seqTest/i101_times.txt"

coding1 = "utf-16"
coding2 = "utf-8"
for file in results:
    print(file)
    f= open(directory+file, 'r', encoding=coding1)
    content= f.read()
    f.close()
    f= open(directory+file, 'w', encoding=coding2)
    f.write(content)
    f.close()