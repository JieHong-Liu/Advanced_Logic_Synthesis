read_blif ./AIG_blif/i10_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/i10_aig_resyn2.blif