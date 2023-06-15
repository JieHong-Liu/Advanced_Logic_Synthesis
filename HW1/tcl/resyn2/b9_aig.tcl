read_blif ./AIG_blif/b9_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/b9_aig_resyn2.blif