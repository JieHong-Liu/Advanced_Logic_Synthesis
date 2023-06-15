read_blif ./AIG_blif/C7552_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/C7552_aig_resyn.blif