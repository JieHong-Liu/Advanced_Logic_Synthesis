read_blif ./AIG_blif/t481_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/t481_aig_resyn.blif