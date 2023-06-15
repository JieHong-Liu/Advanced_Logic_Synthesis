read_blif ./AIG_blif/C6288_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/C6288_aig_resyn2.blif