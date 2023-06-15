read_blif ./AIG_blif/decod_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/decod_aig_resyn.blif