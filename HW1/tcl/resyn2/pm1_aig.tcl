read_blif ./AIG_blif/pm1_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/pm1_aig_resyn2.blif