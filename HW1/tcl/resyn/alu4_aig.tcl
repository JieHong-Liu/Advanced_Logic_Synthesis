read_blif ./AIG_blif/alu4_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/alu4_aig_resyn.blif