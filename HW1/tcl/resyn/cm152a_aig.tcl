read_blif ./AIG_blif/cm152a_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/cm152a_aig_resyn.blif