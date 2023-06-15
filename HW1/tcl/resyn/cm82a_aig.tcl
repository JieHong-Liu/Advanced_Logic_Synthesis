read_blif ./AIG_blif/cm82a_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/cm82a_aig_resyn.blif