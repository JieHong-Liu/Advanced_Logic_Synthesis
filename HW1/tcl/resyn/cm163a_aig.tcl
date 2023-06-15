read_blif ./AIG_blif/cm163a_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/cm163a_aig_resyn.blif