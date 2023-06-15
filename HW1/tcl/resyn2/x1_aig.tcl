read_blif ./AIG_blif/x1_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/x1_aig_resyn2.blif