read_blif ./AIG_blif/example2_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/example2_aig_resyn.blif