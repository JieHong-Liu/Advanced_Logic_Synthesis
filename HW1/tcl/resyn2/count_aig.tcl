read_blif ./AIG_blif/count_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/count_aig_resyn2.blif