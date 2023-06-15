read_blif ./AIG_blif/i1_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/i1_aig_resyn.blif