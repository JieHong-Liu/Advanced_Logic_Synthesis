read_blif ./AIG_blif/des_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/des_aig_resyn.blif