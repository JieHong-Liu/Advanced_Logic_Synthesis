read_blif ./AIG_blif/C499_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/C499_aig_resyn2.blif