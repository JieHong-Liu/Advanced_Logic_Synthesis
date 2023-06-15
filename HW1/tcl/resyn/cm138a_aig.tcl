read_blif ./AIG_blif/cm138a_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/cm138a_aig_resyn.blif