read_blif ./AIG_blif/jc2_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/jc2_aig_resyn.blif