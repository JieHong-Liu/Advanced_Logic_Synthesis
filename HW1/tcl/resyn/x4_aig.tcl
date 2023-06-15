read_blif ./AIG_blif/x4_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/x4_aig_resyn.blif