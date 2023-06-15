read_blif ./AIG_blif/k2_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/k2_aig_resyn.blif