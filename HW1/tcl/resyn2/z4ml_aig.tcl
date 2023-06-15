read_blif ./AIG_blif/z4ml_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/z4ml_aig_resyn2.blif