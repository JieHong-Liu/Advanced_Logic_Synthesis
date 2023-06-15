read_blif ./AIG_blif/cm152a_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/cm152a_aig_resyn2.blif