read_blif ./AIG_blif/ttt2_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/ttt2_aig_resyn2.blif