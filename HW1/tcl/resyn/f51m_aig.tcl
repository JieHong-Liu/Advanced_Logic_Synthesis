read_blif ./AIG_blif/f51m_aig.blif
source ./abc/abc.rc
resyn
write_blif ./resyn_result/f51m_aig_resyn.blif