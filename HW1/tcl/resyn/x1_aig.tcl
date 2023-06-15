read_blif ./AIG_blif/x1_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/x1_aig_resyn.blif