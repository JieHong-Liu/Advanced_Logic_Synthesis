read_blif ./AIG_blif/apex7_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/apex7_aig_resyn2.blif