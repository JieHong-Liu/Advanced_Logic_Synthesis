read_blif ./AIG_blif/i3_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/i3_aig_resyn.blif