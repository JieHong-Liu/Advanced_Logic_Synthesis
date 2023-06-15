read_blif ./AIG_blif/cm163a_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/cm163a_aig_resyn2.blif