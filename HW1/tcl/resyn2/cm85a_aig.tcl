read_blif ./AIG_blif/cm85a_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/cm85a_aig_resyn2.blif