read_blif ./AIG_blif/C2670_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/C2670_aig_resyn.blif