read_blif ./AIG_blif/jc2_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/jc2_aig_resyn2.blif