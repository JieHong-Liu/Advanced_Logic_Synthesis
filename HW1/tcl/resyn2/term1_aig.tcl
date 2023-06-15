read_blif ./AIG_blif/term1_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/term1_aig_resyn2.blif