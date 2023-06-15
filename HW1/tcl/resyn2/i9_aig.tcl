read_blif ./AIG_blif/i9_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/i9_aig_resyn2.blif