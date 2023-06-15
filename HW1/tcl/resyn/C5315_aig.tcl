read_blif ./AIG_blif/C5315_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/C5315_aig_resyn.blif