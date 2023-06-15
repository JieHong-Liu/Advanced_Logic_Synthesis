read_blif ./AIG_blif/C17_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/C17_aig_resyn.blif