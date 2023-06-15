read_blif ./AIG_blif/cmb_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/cmb_aig_resyn.blif