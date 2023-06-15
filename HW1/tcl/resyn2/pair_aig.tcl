read_blif ./AIG_blif/pair_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/pair_aig_resyn2.blif