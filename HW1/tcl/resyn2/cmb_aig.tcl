read_blif ./AIG_blif/cmb_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/cmb_aig_resyn2.blif