read_blif ./AIG_blif/lal_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/lal_aig_resyn.blif