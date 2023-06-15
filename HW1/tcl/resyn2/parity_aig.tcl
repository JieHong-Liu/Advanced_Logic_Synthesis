read_blif ./AIG_blif/parity_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/parity_aig_resyn2.blif