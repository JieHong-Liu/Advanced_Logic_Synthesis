read_blif ./AIG_blif/cm151a_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/cm151a_aig_resyn.blif