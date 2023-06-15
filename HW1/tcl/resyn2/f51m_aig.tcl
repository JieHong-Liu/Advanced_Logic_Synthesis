read_blif ./AIG_blif/f51m_aig.blif
source ./abc/abc.rc
resyn2
write_blif ./resyn2_result/f51m_aig_resyn2.blif