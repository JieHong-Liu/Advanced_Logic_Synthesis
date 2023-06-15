read_blif ./AIG_blif/lal_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/lal_aig_resyn2.blif