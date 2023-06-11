import os

def list_files_in_directory(directory):
    for filename in os.listdir(directory):
        if(filename == "testcase.tar.gz"):
            pass
        filepath = os.path.join(directory, filename)
        inputFolder = './resource/benchmarks/'
        outputFolder = './outputBLIF/'
        # powerFolder = './power_result/'
        powerFolder = './power_initial/'
        if os.path.isfile(filepath):
            outputFile = filename.split('.')[0] + ".blif"
            outputStr = "./bin/sa " + inputFolder + filename + ' ' + outputFolder + outputFile + "\n"
            outputStr += "./sis -xf tcl/" + filename.split('.')[0]+ ".tcl > " + powerFolder + filename.split('.')[0] + ".txt" 
            writeTCL(outputFolder + outputFile,filename.split('.')[0]+".tcl")
            print(outputStr)

def writeTCL(blifName, outputTCL):
    with open ('tcl/'+outputTCL, 'w') as f:
        tcl_pattern = 'read_blif ' + blifName + '\n'
        tcl_pattern += 'source ./resource/sis_script/opt_map_power.scr' + '\n'
        f.write(tcl_pattern)


# main
# select folder path
folder_path = 'resource/benchmarks/'
list_files_in_directory(folder_path)
print("Conversion and TCL is finished!!!")
