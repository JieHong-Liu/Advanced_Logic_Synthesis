read_blif ./AIG_blif/go_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/go_aig_resyn2.blif