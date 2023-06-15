read_blif ./AIG_blif/tcon_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/tcon_aig_resyn.blif