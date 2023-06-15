read_blif ./AIG_blif/pair_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/pair_aig_resyn.blif