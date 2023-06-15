read_blif ./AIG_blif/too_large_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/too_large_aig_resyn2.blif