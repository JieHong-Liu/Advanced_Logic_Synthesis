read_blif ./AIG_blif/frg2_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/frg2_aig_resyn2.blif