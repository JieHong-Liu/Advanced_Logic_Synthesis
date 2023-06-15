read_blif ./AIG_blif/C7552_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/C7552_aig_resyn2.blif