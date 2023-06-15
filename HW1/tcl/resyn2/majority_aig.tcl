read_blif ./AIG_blif/majority_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/majority_aig_resyn2.blif