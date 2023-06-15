read_blif ./AIG_blif/i2_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/i2_aig_resyn2.blif