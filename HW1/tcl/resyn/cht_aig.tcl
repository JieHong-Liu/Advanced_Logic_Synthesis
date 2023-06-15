read_blif ./AIG_blif/cht_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/cht_aig_resyn.blif