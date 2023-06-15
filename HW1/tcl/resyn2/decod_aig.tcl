read_blif ./AIG_blif/decod_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/decod_aig_resyn2.blif