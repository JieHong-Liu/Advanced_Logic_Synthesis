read_blif ./AIG_blif/c8_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/c8_aig_resyn.blif