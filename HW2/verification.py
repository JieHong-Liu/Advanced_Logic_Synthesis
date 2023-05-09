import subprocess
import os
import csv
from os import listdir

# a method that get the filelist from path

def getDirList(path):
    dirList = listdir(path)
    return dirList

def verification(filePath,key_value) -> bool: # this method return True or False to express the result is True or not
    if (not key_value): # key value is empty means it didn't finished!
        print('key_value is empty')
        return False
    else:
        binary_file="./bin/lcmp" # usage: ./bin/lcmp original_circuit locking_circuit key=key_value
        arguments = ['','','']
        fileName  = filePath.split('/')[-1]
        if(filePath.split('/')[0] == 'sarlock'):
            arguments[0] = './benchmarks/sarlock/original/' + fileName.split('_')[0] + 'bench'
        else:
            arguments[0] = './benchmarks/original/' + fileName.split('_')[0] + '.bench' 
        arguments[1] = './benchmarks/' + filePath
        arguments[2] = 'key=' + key_value
        # print(arguments)
        result = subprocess.run([binary_file] + arguments,  capture_output=True, text=True) 
        # print('result.stdout=', result.stdout)
        if(result.stdout.strip() == 'equivalent'):
            return True
        else:
            return False

def main():

    # read output.txt 
    filename = 'results/0508/output-0508.csv'
    # Read the existing CSV file
    with open(filename, 'r+') as file:
        reader = csv.reader(file)
        rows = list(reader)
        failed_count = 0
        for row in rows:
            if row == rows[0]:
                row.append('VERIFICATION RESULT')
                continue # Skip the first row.
            elif (row[-1] == 'x'):
                failed_count += 1 
                row.append("no need")
                print("No need to verification")
            else:
                ver_result = verification(row[0],row[-1])
                if(ver_result == True):
                    print("Verification pass !!!")
                else:
                    print(row[0], "Verification fail !!!")
                row.append(ver_result)
        print("There is ", failed_count , " datas can't finished ATTACK!!!")
    
        with open('results/0508/ver-output.csv','a') as ver_file:
            writer = csv.writer(ver_file)
            writer.writerows(rows)



main()