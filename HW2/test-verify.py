import subprocess
import os
from os import listdir


# a method that get the filelist from path

def getDirList(path):
    dirList = listdir(path)
    return dirList

def decryption(filePath,arguments) -> str: # return key_value
    binary_file="./bin/sld"
    timeout_seconds = 10
    # Open file to write output
    with open("sarlock-tmp.txt", "w") as tmpFile:
        finished = True
        try:
            subprocess.run([binary_file] + arguments,  stdout=tmpFile, timeout=timeout_seconds)
            # parse the tmp.txt, and print the last line 
        except subprocess.TimeoutExpired:
            outputData = ('Timeout occurred for ' + filePath + '\n')
            finished = False
            print(filePath + " is not finished !!!")

    if(finished == True):
        with open('sarlock-tmp.txt', 'r') as tmpFile:
            lines = tmpFile.readlines()
            outputData = filePath + ' ' + lines[0].strip() + ' ' + lines[-1].strip() + ' ' +  lines[-2].strip() + '\n'
            print(filePath + " is finished!!!")
            words = outputData.split()
            # get the locking key value
            for word in words:
                if word.startswith('key='):
                    key_value=word[4:]
    else:
        key_value=''
    with open("sarlock-output.txt", 'a') as output:
        output.write(outputData)
        print(outputData)

    os.remove('sarlock-tmp.txt')
    return key_value



def main():
   
    benchmarks = ['sarlock/dac12/'] # not sure why sarlock need to attack dividely.
    # save the fileList into fileList 2D vector.
    fileList=[]
    for i in range(len(benchmarks)):
        tmpDesign = getDirList("benchmarks/"+benchmarks[i])
        fileList.append(tmpDesign)
    # modify arguments every iterations
    for i in range(len(fileList)):
        arguments=["",""]
        for design in fileList[i]:
            arguments[0] = './benchmarks/' + benchmarks[i] + design
            if(benchmarks[i] == 'sarlock/dac12/'):
                arguments[1] = './benchmarks/sarlock/original/' + design.split('_')[0] + '.bench'
            else:
                arguments[1] = './benchmarks/original/' + design.split('_')[0] + '.bench'
            key_value = decryption(benchmarks[i]+design,arguments)
            verify_result = verification('./benchmarks/'+ benchmarks[i]+design,key_value)

        print("========")

main()