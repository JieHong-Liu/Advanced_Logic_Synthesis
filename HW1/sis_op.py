import os
from os import listdir

# write tcl for sis


## Generate TCL to implement this flow (script and rugged)

aig_path = './AIG_blif/'
fileNames = listdir(aig_path)

for fileName in fileNames:
    f_name = fileName[:-5] # without .blif

    tcl_pattern_result = 'read_blif ./AIG_blif/' + fileName + '\n'
    tcl_pattern_result += 'print_stats'

    tcl_file = open ('./tcl/origin/'+f_name+'.tcl', 'w') # calculate for origin literals
    tcl_file.write(tcl_pattern_result)
    tcl_file.close()
# execute TCL to generate origin literal result
origin_path = './tcl/origin/'
fileNames = listdir(origin_path)
for fileName in fileNames:
    f_name = fileName[:-4] # without .tcl
    os.system('./sis -xf '+origin_path+fileName + '> log/origin/'+f_name+'.txt') 


aig_path = './AIG_blif/'
fileNames = listdir(aig_path)

for fileName in fileNames:
    f_name = fileName[:-5] # without .blif

    tcl_pattern_result = 'read_blif ./AIG_blif/' + fileName 
    tcl_pattern_result2 = tcl_pattern_result

    tcl_pattern_result += '\n' + 'source ./sis1.3/sis/sis_lib/script.rugged' + '\n'
    tcl_pattern_result2 += '\n' + 'source ./sis1.3/sis/sis_lib/script' + '\n'

    tcl_pattern_result += 'print_stats'
    tcl_pattern_result2 += 'print_stats'


    tcl_file = open ('./tcl/rugged/'+f_name+'.tcl', 'w')
    tcl_file.write(tcl_pattern_result)
    tcl_file.close()

    tcl_file = open ('./tcl/script/'+f_name+'.tcl', 'w')
    tcl_file.write(tcl_pattern_result2)
    tcl_file.close()

# read the tcl and command them

tcl_path = './tcl/rugged/'
tcl_path2 = './tcl/script/'
fileNames = listdir(tcl_path)

for fileName in fileNames:
    f_name = fileName[:-4] # without .tcl
    print(f_name)
    os.system('./sis -xf '+tcl_path+fileName + '> log/rugged/'+f_name+'.txt') 
    os.system('./sis -xf '+tcl_path2+fileName + '> log/script/'+f_name+'.txt')


## Generate TCL to print result of abc (resyn and resyn2)


resyn_path = './resyn_result/'
fileNames = listdir(resyn_path)


for fileName in fileNames:
    f_name = fileName[:-5] # without .blif

    tcl_pattern_result = 'read_blif ./resyn_result/' + fileName + '\n'
    tcl_pattern_result += 'print_stats'
    tcl_file = open ('./tcl/sis_resyn/'+f_name+'.tcl', 'w')
    tcl_file.write(tcl_pattern_result)
    tcl_file.close()

resyn2_path = './resyn2_result/'
fileNames = listdir(resyn2_path)
for fileName in fileNames:
    f_name = fileName[:-5] # without .blif

    tcl_pattern_result = 'read_blif ./resyn2_result/' + fileName + '\n'
    tcl_pattern_result += 'print_stats'
    tcl_file = open ('./tcl/sis_resyn2/'+f_name+'.tcl', 'w')
    tcl_file.write(tcl_pattern_result)
    tcl_file.close()

# read the tcl and command them

tcl_path = './tcl/sis_resyn/'
fileNames = listdir(tcl_path)

for fileName in fileNames:
    f_name = fileName[:-4] # without .tcl
    print(f_name)
    os.system('./sis -xf '+tcl_path+fileName + '> log/resyn/'+f_name+'.txt') 

tcl_path2 = './tcl/sis_resyn2/'
fileNames = listdir(tcl_path2)

for fileName in fileNames:
    f_name = fileName[:-4] # without .tcl
    print(f_name)
    os.system('./sis -xf '+tcl_path2+fileName + '> log/resyn2/'+f_name+'.txt') 



# parser for log

## read script 

## read rugged

## read resyn

## read resyn2



