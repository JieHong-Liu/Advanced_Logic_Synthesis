read_blif ./AIG_blif/c8_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/c8_aig_resyn2.blif