read_blif ./AIG_blif/C432_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/C432_aig_resyn2.blif