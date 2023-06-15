read_blif ./AIG_blif/b1_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/b1_aig_resyn2.blif