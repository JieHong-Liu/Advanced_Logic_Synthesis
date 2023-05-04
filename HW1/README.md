## proposal: Using Python script to generate TCL command to compare the result in ABC and SIS.

+ The proposed tcl is as below:
    1. input to output.blif
        ```tcl=
        read_blif ./mcnc/mlex/fileName.blif
        strash
        write_blif 
        ```
    2. Use python script to generate tcl pattern in 'tcl_pattern'
    3. Generate sis tcl.
        ```tcl=
        read_blif ./AIG_blif/C17_aig.blif
        source ./sis1.3/sis/sis_lib/script.rugged
        print_stats
        ```
## Benchmark

+ This work use MCNC benchmark to perform experiment.

## Method

+ `sis_op.py` to operate sis 
+ `abc_op.py` to operate abc 
+ `read_log.py` would read log from csv
