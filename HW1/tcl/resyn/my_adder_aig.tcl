read_blif ./AIG_blif/my_adder_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/my_adder_aig_resyn.blif