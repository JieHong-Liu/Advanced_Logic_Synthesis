read_blif ./AIG_blif/example2_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/example2_aig_resyn2.blif