read_blif ./AIG_blif/parity_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/parity_aig_resyn.blif