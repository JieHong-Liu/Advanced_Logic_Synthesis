read_blif ./AIG_blif/C432_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/C432_aig_resyn.blif