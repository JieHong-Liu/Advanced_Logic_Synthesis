read_blif ./AIG_blif/C499_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/C499_aig_resyn.blif