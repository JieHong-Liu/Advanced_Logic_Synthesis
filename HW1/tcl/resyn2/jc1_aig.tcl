read_blif ./AIG_blif/jc1_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/jc1_aig_resyn2.blif