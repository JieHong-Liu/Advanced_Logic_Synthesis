read_blif ./AIG_blif/i8_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/i8_aig_resyn2.blif