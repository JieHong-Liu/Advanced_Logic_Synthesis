read_blif ./AIG_blif/cu_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/cu_aig_resyn2.blif