read_blif ./AIG_blif/i7_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/i7_aig_resyn.blif