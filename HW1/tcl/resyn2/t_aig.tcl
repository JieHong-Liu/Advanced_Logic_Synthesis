read_blif ./AIG_blif/t_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/t_aig_resyn2.blif