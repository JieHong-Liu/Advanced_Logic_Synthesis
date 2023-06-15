read_blif ./AIG_blif/sct_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/sct_aig_resyn.blif