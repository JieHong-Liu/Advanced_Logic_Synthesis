import subprocess
import os
from os import listdir


# a method that get the filelist from path

def getDirList(path):
    dirList = listdir(path)
    return dirList

def decryption(filePath,arguments):# Open binary file and exeute command with arguments
    binary_file="./bin/sld"
    timeout_seconds = 7200
    # Open file to write output
    with open("dac-tmp.txt", "w") as tmpFile:
        finished = True
        try:
            subprocess.run([binary_file] + arguments,  stdout=tmpFile, timeout=timeout_seconds) #k2_enc25 is a problem
            # parse the tmp.txt, and print the last line 
        except subprocess.TimeoutExpired:
            outputData = ('Timeout occurred for ' + filePath + '\n')
            finished = False
            print(filePath + " is not finished !!!")

    if(finished == True):
        with open('dac-tmp.txt', 'r') as tmpFile:
            lines = tmpFile.readlines()
            outputData = filePath + ' ' + lines[0].strip() + ' ' + lines[-1].strip() + ' ' +  lines[-2].strip() + '\n'
            print(filePath + " is finished!!")

    with open("dac-output.txt", 'a') as output:
        output.write(outputData)
        print(outputData)

    os.remove('dac-tmp.txt')

def main():
   
    benchmarks = ['dac12/'] # run dac12/ only
    # save the fileList into fileList 2D vector.
    fileList=[]
    for i in range(len(benchmarks)):
        tmpDesign = getDirList("benchmarks/"+benchmarks[i])
        fileList.append(tmpDesign)
    print("fileList before sort: ",fileList)
    print("fileList: ", fileList[0])
    fileList[0].sort()
    print("fileList after sorted: ",fileList)
    # modify arguments every iterations
    for i in range(len(fileList)):
        arguments=["",""]
        for design in fileList[i]:
            arguments[0] = './benchmarks/' + benchmarks[i] + design
            # arguments[1] = './benchmarks/original/' + design.split('_')[0] + '.bench'
            if(benchmarks[i] == 'sarlock/dac12/'):
                arguments[1] = './benchmarks/sarlock/original/' + design.split('_')[0] + '.bench'
            else:
                arguments[1] = './benchmarks/original/' + design.split('_')[0] + '.bench'
            decryption(benchmarks[i]+design,arguments)
        print("========")

main()
