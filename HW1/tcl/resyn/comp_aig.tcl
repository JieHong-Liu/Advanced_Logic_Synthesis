read_blif ./AIG_blif/comp_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/comp_aig_resyn.blif