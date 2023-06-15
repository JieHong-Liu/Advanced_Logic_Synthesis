read_blif ./AIG_blif/i5_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/i5_aig_resyn.blif