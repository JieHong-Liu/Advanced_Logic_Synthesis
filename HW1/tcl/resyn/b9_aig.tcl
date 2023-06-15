read_blif ./AIG_blif/b9_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/b9_aig_resyn.blif