read_blif ./AIG_blif/frg2_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/frg2_aig_resyn.blif