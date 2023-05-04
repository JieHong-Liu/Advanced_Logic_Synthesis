import os
import csv
from os import listdir


def read_log(path):
    pathName = path.split('/')[2] # script, rugged....
    with open(pathName+'.csv','w') as file:
        csvwriter = csv.writer(file)
        fileNames = listdir(path)
        fileNames.sort()
        for fileName in fileNames:
            f = open(path+fileName, 'r')
            line = f.readline()
            line = f.readline().split('=')[-1].strip()
            print(fileName, line)
            csvwriter.writerow([fileName,line])

origin_path = './log/origin/'
script_path = './log/script/'
rugged_path = './log/rugged/'
resyn_path = './log/resyn/'
resyn2_path = './log/resyn2/'

read_log(origin_path)
read_log(script_path)
read_log(rugged_path)
read_log(resyn_path)
read_log(resyn2_path)


