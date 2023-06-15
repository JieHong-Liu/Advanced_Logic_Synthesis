read_blif ./AIG_blif/C6288_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/C6288_aig_resyn.blif