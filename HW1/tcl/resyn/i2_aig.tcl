read_blif ./AIG_blif/i2_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/i2_aig_resyn.blif