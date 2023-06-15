# This script would demo one testcase in our algorithm and SIS optimization
make
./bin/sa ./resource/benchmarks/s27_opt.kiss ./outputBLIF/s27_opt.blif
echo "MY result:"
./sis -xf ./tcl/s27_opt.tcl
echo "SIS result:"
./sis -xf ./demoTCL/s27_opt.tcl