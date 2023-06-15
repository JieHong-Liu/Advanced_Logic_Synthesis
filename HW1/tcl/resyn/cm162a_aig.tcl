read_blif ./AIG_blif/cm162a_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/cm162a_aig_resyn.blif