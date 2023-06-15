read_blif ./AIG_blif/C1355_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/C1355_aig_resyn2.blif