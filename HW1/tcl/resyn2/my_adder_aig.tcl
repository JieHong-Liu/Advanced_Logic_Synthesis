read_blif ./AIG_blif/my_adder_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/my_adder_aig_resyn2.blif