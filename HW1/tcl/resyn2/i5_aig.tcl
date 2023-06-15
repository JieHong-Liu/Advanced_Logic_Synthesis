read_blif ./AIG_blif/i5_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/i5_aig_resyn2.blif