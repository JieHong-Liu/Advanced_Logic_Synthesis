read_blif ./AIG_blif/vda_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/vda_aig_resyn.blif