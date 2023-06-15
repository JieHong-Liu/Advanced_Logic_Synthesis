read_blif ./AIG_blif/b1_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/b1_aig_resyn.blif