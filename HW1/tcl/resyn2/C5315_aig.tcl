read_blif ./AIG_blif/C5315_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/C5315_aig_resyn2.blif