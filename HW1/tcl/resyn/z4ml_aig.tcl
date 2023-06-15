read_blif ./AIG_blif/z4ml_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/z4ml_aig_resyn.blif