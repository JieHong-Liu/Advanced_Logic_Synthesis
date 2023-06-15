read_blif ./AIG_blif/comp_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/comp_aig_resyn2.blif