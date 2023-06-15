read_blif ./AIG_blif/x4_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/x4_aig_resyn2.blif