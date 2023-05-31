def kiss_to_blif(kiss_file, blif_file):
    # read kiss file
    lines=''
    with open(kiss_file, 'r') as f:
        lines = f.readlines()
    # write blif file
    with open(blif_file, 'w') as f:
        # write .model FSM name
        f.write(".model justinFSM\n")
        # write all kiss file into blif file
        f.writelines(lines)
        # state encoding
        f.write(".code S0 00\n")
        f.write(".code S1 01\n")
        f.write(".code S2 10\n")
        f.write(".code S3 11\n")
        f.write(".end\n")

def gen_tcl(blif_file):
    with open ('tcl/test.tcl','w') as f:
        tcl_pattern = 'read_blif' + blif_file + '\n'
        tcl_pattern += 'source ./resource/sis_script/opt_map_power.scr'
        f.write(tcl_pattern)

# main
kiss_file = 'resource/benchmarks/beecount_opt.kiss'
blif_file = 'blif_gen/beecount.blif'
kiss_to_blif(kiss_file, blif_file)
gen_tcl(blif_file)
print("Conversion and TCL is finished!!!")
