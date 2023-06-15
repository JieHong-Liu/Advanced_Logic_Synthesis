read_blif ./AIG_blif/cc_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/cc_aig_resyn.blif