read_blif ./AIG_blif/apex6_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/apex6_aig_resyn.blif