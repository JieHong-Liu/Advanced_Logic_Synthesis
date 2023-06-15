read_blif ./AIG_blif/majority_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/majority_aig_resyn.blif