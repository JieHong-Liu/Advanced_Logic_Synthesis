read_blif ./AIG_blif/cht_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/cht_aig_resyn2.blif