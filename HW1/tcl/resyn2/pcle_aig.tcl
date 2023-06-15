read_blif ./AIG_blif/pcle_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/pcle_aig_resyn2.blif