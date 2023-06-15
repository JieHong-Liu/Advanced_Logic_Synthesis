read_blif ./AIG_blif/C1908_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/C1908_aig_resyn2.blif