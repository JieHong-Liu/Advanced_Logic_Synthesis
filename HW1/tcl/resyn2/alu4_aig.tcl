read_blif ./AIG_blif/alu4_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/alu4_aig_resyn2.blif