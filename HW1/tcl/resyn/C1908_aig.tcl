read_blif ./AIG_blif/C1908_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/C1908_aig_resyn.blif