read_blif ./AIG_blif/t_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/t_aig_resyn.blif