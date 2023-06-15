read_blif ./AIG_blif/cu_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/cu_aig_resyn.blif