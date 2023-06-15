read_blif ./AIG_blif/i1_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/i1_aig_resyn2.blif