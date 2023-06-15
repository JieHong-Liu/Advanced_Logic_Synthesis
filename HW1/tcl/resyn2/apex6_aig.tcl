read_blif ./AIG_blif/apex6_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/apex6_aig_resyn2.blif