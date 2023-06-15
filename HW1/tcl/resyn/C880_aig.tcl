read_blif ./AIG_blif/C880_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/C880_aig_resyn.blif