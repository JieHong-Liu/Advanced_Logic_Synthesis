read_blif ./AIG_blif/unreg_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/unreg_aig_resyn2.blif