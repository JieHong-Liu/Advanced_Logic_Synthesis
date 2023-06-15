read_blif ./AIG_blif/i7_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/i7_aig_resyn2.blif