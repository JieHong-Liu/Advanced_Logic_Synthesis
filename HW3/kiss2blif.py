def gen_tcl(blif_file):
    with open ('tcl/test.tcl','w') as f:
        tcl_pattern = 'read_blif' + blif_file + '\n'
        tcl_pattern += 'source ./resource/sis_script/opt_map_power.scr'
        f.write(tcl_pattern)

# main

gen_tcl(blif_file)
print("Conversion and TCL is finished!!!")
