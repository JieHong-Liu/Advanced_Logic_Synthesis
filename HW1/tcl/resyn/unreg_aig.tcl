read_blif ./AIG_blif/unreg_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/unreg_aig_resyn.blif