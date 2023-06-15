read_blif ./AIG_blif/i8_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/i8_aig_resyn.blif