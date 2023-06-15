read_blif ./AIG_blif/t481_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/t481_aig_resyn2.blif