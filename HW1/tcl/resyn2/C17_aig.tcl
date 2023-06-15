read_blif ./AIG_blif/C17_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/C17_aig_resyn2.blif