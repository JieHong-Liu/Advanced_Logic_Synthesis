read_blif ./AIG_blif/i10_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/i10_aig_resyn.blif