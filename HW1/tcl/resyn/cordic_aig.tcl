read_blif ./AIG_blif/cordic_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/cordic_aig_resyn.blif