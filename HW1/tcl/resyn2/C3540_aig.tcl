read_blif ./AIG_blif/C3540_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/C3540_aig_resyn2.blif