read_blif ./AIG_blif/sct_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/sct_aig_resyn2.blif