read_blif ./AIG_blif/apex7_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/apex7_aig_resyn.blif