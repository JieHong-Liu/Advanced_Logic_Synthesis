make
./bin/sa ./resource/benchmarks/s27_opt.kiss ./outputBLIF/s27_opt.blif
./sis -xf tcl/s27_opt.tcl > ./power_result/s27_opt.txt
./bin/sa ./resource/benchmarks/paper_example.kiss ./outputBLIF/paper_example.blif
./sis -xf tcl/paper_example.tcl > ./power_result/paper_example.txt
./bin/sa ./resource/benchmarks/dk14_opt.kiss ./outputBLIF/dk14_opt.blif
./sis -xf tcl/dk14_opt.tcl > ./power_result/dk14_opt.txt
./bin/sa ./resource/benchmarks/ex1_opt.kiss ./outputBLIF/ex1_opt.blif
./sis -xf tcl/ex1_opt.tcl > ./power_result/ex1_opt.txt
./bin/sa ./resource/benchmarks/bbsse_opt.kiss ./outputBLIF/bbsse_opt.blif
./sis -xf tcl/bbsse_opt.tcl > ./power_result/bbsse_opt.txt
./bin/sa ./resource/benchmarks/cse_opt.kiss ./outputBLIF/cse_opt.blif
./sis -xf tcl/cse_opt.tcl > ./power_result/cse_opt.txt
./bin/sa ./resource/benchmarks/bbara_opt.kiss ./outputBLIF/bbara_opt.blif
./sis -xf tcl/bbara_opt.tcl > ./power_result/bbara_opt.txt
./bin/sa ./resource/benchmarks/beecount_opt.kiss ./outputBLIF/beecount_opt.blif
./sis -xf tcl/beecount_opt.tcl > ./power_result/beecount_opt.txt
./bin/sa ./resource/benchmarks/sample.kiss ./outputBLIF/sample.blif
./sis -xf tcl/sample.tcl > ./power_result/sample.txt
./bin/sa ./resource/benchmarks/bbtas_opt.kiss ./outputBLIF/bbtas_opt.blif
./sis -xf tcl/bbtas_opt.tcl > ./power_result/bbtas_opt.txt
./bin/sa ./resource/benchmarks/dk16_opt.kiss ./outputBLIF/dk16_opt.blif
./sis -xf tcl/dk16_opt.tcl > ./power_result/dk16_opt.txt
./bin/sa ./resource/benchmarks/snad_opt.kiss ./outputBLIF/snad_opt.blif
./sis -xf tcl/snad_opt.tcl > ./power_result/snad_opt.txt

# ./bin/sa ./resource/benchmarks/s27_opt.kiss ./outputBLIF/s27_opt.blif
# ./sis -xf tcl/s27_opt.tcl > ./power_initial/s27_opt.txt
# ./bin/sa ./resource/benchmarks/paper_example.kiss ./outputBLIF/paper_example.blif
# ./sis -xf tcl/paper_example.tcl > ./power_initial/paper_example.txt
# ./bin/sa ./resource/benchmarks/dk14_opt.kiss ./outputBLIF/dk14_opt.blif
# ./sis -xf tcl/dk14_opt.tcl > ./power_initial/dk14_opt.txt
# ./bin/sa ./resource/benchmarks/ex1_opt.kiss ./outputBLIF/ex1_opt.blif
# ./sis -xf tcl/ex1_opt.tcl > ./power_initial/ex1_opt.txt
# ./bin/sa ./resource/benchmarks/bbsse_opt.kiss ./outputBLIF/bbsse_opt.blif
# ./sis -xf tcl/bbsse_opt.tcl > ./power_initial/bbsse_opt.txt
# ./bin/sa ./resource/benchmarks/cse_opt.kiss ./outputBLIF/cse_opt.blif
# ./sis -xf tcl/cse_opt.tcl > ./power_initial/cse_opt.txt
# ./bin/sa ./resource/benchmarks/bbara_opt.kiss ./outputBLIF/bbara_opt.blif
# ./sis -xf tcl/bbara_opt.tcl > ./power_initial/bbara_opt.txt
# ./bin/sa ./resource/benchmarks/beecount_opt.kiss ./outputBLIF/beecount_opt.blif
# ./sis -xf tcl/beecount_opt.tcl > ./power_initial/beecount_opt.txt
# ./bin/sa ./resource/benchmarks/sample.kiss ./outputBLIF/sample.blif
# ./sis -xf tcl/sample.tcl > ./power_initial/sample.txt
# ./bin/sa ./resource/benchmarks/bbtas_opt.kiss ./outputBLIF/bbtas_opt.blif
# ./sis -xf tcl/bbtas_opt.tcl > ./power_initial/bbtas_opt.txt
# ./bin/sa ./resource/benchmarks/dk16_opt.kiss ./outputBLIF/dk16_opt.blif
# ./sis -xf tcl/dk16_opt.tcl > ./power_initial/dk16_opt.txt
# ./bin/sa ./resource/benchmarks/snad_opt.kiss ./outputBLIF/snad_opt.blif
# ./sis -xf tcl/snad_opt.tcl > ./power_initial/snad_opt.txt

echo "State Assignment is done!"