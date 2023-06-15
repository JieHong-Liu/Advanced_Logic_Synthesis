import os

def list_files_in_directory(directory):
    for filename in os.listdir(directory):
        if(filename == "testcase.tar.gz"):
            pass
        filepath = os.path.join(directory, filename)
        inputFolder = './resource/benchmarks/'
        outputFolder = './demoTCL/'
        # powerFolder = './power_initial/'
        if os.path.isfile(filepath):
            inputFileName = inputFolder + filename
            outputFileName = outputFolder + filename.split('.')[0] + '.tcl'
            print(inputFileName, outputFileName)
            writeTCL(inputFileName, outputFileName)

def writeTCL(inputFileName, outputFileName):
    with open (outputFileName, 'w') as f:
        tcl_pattern = 'read_kiss ' + inputFileName + '\n'
        tcl_pattern += 'state_assign' + '\n'
        tcl_pattern += 'source ./resource/sis_script/opt_map_power.scr' + '\n'
        f.write(tcl_pattern)


# main
# select folder path
folder_path = 'resource/benchmarks/'
list_files_in_directory(folder_path)
print("Conversion and TCL is finished!!!")
