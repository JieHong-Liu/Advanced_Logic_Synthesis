read_blif ./AIG_blif/count_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/count_aig_resyn.blif