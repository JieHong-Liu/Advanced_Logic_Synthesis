read_blif ./AIG_blif/pm1_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/pm1_aig_resyn.blif