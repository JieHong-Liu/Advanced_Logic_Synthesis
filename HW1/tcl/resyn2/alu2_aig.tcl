read_blif ./AIG_blif/alu2_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/alu2_aig_resyn2.blif