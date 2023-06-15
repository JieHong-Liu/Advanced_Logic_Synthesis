read_blif ./AIG_blif/C880_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/C880_aig_resyn2.blif