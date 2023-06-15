read_blif ./AIG_blif/des_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/des_aig_resyn2.blif