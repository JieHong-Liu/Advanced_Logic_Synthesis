read_blif ./AIG_blif/cm42a_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/cm42a_aig_resyn.blif