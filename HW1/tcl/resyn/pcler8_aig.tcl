read_blif ./AIG_blif/pcler8_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/pcler8_aig_resyn.blif