read_blif ./AIG_blif/x2_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/x2_aig_resyn2.blif