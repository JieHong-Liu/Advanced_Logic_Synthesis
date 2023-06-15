read_blif ./AIG_blif/x2_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/x2_aig_resyn.blif