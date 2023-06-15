read_blif ./AIG_blif/dalu_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/dalu_aig_resyn2.blif