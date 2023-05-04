# this file is to generate tcl file, and the purpose is generate "aig" blif file.

import os
from os import listdir
# read blif from mcnc/mlex/
blif_path = './mcnc/mlex'
# get files name from the path
fileNames = listdir(blif_path)


# write tcl 
for fileName in fileNames:
    f_name = fileName[:-5] # without .blif
    tcl_pattern_result = 'read_blif ./mcnc/mlex/' + fileName 
    tcl_pattern_result += '\n' + 'strash' + '\n'
    tcl_pattern_result += 'write_blif ./AIG_blif/' + f_name + '_aig.blif'
    
    tcl_file = open ('./tcl/aig/'+f_name+'.tcl', 'w')
    tcl_file.write(tcl_pattern_result)
    tcl_file.close()

# read tcl file and command them.
tcl_path = './tcl/aig'
fileNames = listdir(tcl_path)
for fileName in fileNames:
    os.system('./abc_bin -xf '+'./tcl/aig/'+fileName) # example: ./abc_bin -xf ./tcl/C17.tcl   





# Then, we have output_aig.blif, we want to use resyn script and write them into blif file as resyn_C17.blif

## Generate TCL to implement this flow (resyn and resyn2)

aig_path = './AIG_blif'
fileNames = listdir(aig_path)

for fileName in fileNames:
    f_name = fileName[:-5] # without .blif

    tcl_pattern_result = 'read_blif ./AIG_blif/' + fileName 

    tcl_pattern_result += '\n' + 'source ./abc/abc.rc' + '\n'
    tcl_pattern_result2 = tcl_pattern_result # for resyn2
    
    tcl_pattern_result += 'resyn' +'\n'
    tcl_pattern_result2 += 'resyn2' + '\n'

    tcl_pattern_result += 'write_blif ./resyn_result/' + f_name + '_resyn.blif'
    tcl_pattern_result2 += 'write_blif ./resyn2_result/' + f_name + '_resyn2.blif'

    tcl_file = open ('./tcl/resyn/'+f_name+'.tcl', 'w')
    tcl_file.write(tcl_pattern_result)
    tcl_file.close()

    tcl_file = open ('./tcl/resyn2/'+f_name+'.tcl', 'w')
    tcl_file.write(tcl_pattern_result2)
    tcl_file.close()

# read tcl file and command them.
tcl_path = './tcl/resyn/'
tcl_path2 = './tcl/resyn2/'
fileNames = listdir(tcl_path)
for fileName in fileNames:
    os.system('./abc_bin -xf '+tcl_path+fileName) 
    os.system('./abc_bin -xf '+tcl_path2+fileName)




