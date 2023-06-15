read_blif ./AIG_blif/mux_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/mux_aig_resyn2.blif