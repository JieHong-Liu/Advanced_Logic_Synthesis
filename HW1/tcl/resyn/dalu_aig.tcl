read_blif ./AIG_blif/dalu_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/dalu_aig_resyn.blif