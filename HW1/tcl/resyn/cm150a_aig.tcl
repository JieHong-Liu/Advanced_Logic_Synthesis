read_blif ./AIG_blif/cm150a_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/cm150a_aig_resyn.blif