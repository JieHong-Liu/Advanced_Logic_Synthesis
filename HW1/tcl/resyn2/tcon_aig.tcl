read_blif ./AIG_blif/tcon_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/tcon_aig_resyn2.blif