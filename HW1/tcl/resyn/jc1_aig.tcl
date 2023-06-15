read_blif ./AIG_blif/jc1_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/jc1_aig_resyn.blif