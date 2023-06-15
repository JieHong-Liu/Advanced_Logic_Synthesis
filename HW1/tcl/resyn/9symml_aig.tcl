read_blif ./AIG_blif/9symml_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/9symml_aig_resyn.blif