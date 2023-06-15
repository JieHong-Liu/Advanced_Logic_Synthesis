read_blif ./AIG_blif/9symml_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/9symml_aig_resyn2.blif