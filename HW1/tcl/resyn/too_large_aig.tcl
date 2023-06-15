read_blif ./AIG_blif/too_large_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/too_large_aig_resyn.blif