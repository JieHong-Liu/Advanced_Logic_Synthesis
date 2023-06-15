read_blif ./AIG_blif/i3_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/i3_aig_resyn2.blif