read_blif ./AIG_blif/frg1_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/frg1_aig_resyn.blif