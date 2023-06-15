read_blif ./AIG_blif/x3_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/x3_aig_resyn.blif