read_blif ./AIG_blif/C3540_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/C3540_aig_resyn.blif