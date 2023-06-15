read_blif ./AIG_blif/go_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/go_aig_resyn.blif