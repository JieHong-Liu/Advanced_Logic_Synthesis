read_blif ./AIG_blif/i6_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/i6_aig_resyn2.blif