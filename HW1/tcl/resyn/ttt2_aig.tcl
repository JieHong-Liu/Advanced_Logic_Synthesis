read_blif ./AIG_blif/ttt2_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/ttt2_aig_resyn.blif