read_blif ./AIG_blif/term1_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/term1_aig_resyn.blif