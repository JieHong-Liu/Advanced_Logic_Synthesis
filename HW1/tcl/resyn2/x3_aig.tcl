read_blif ./AIG_blif/x3_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/x3_aig_resyn2.blif