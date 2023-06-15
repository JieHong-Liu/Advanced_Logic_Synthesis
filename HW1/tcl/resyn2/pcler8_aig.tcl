read_blif ./AIG_blif/pcler8_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/pcler8_aig_resyn2.blif