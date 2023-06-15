read_blif ./AIG_blif/rot_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/rot_aig_resyn.blif