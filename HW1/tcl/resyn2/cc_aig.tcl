read_blif ./AIG_blif/cc_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/cc_aig_resyn2.blif