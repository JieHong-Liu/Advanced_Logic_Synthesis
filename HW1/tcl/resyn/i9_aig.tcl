read_blif ./AIG_blif/i9_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/i9_aig_resyn.blif