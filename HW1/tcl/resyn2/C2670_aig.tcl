read_blif ./AIG_blif/C2670_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/C2670_aig_resyn2.blif