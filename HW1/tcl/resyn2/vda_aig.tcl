read_blif ./AIG_blif/vda_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/vda_aig_resyn2.blif