read_blif ./AIG_blif/i6_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/i6_aig_resyn.blif