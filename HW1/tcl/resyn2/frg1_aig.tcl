read_blif ./AIG_blif/frg1_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/frg1_aig_resyn2.blif