read_blif ./AIG_blif/pcle_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/pcle_aig_resyn.blif