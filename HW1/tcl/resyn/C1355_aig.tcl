read_blif ./AIG_blif/C1355_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/C1355_aig_resyn.blif