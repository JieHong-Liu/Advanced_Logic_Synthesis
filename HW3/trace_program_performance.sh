# valgrind --tool=callgrind --trace-children=yes ./build/dramsim3main configs/DDR4_8Gb_x8_3200.ini -c 1000000 -t sample_trace.txt
# valgrind --tool=callgrind --trace-children=yes ./build/dramsim3main configs/DDR4_8Gb_x8_3200.ini -c 1000050 -t extrem_trace.txt -m yes

# make
# valgrind --tool=callgrind --trace-children=yes --callgrind-out-file=call_grind.txt ./dramsim3main.out configs/DDR4_8Gb_x8_3200.ini -c 1000050 -t extrem_trace.txt -m yes
# cd ../gprof2dot
# python gprof2dot.py -f callgrind  -s ../DRAMsim3_cmd_v1/call_grind.txt > out.dot
# dot -Tpng out.dot -o call_grind_out.png
# mv call_grind_out.png ../DRAMsim3_cmd_v1/
# cd ../DRAMsim3_cmd_v1/


# make
# valgrind --tool=callgrind --trace-children=yes --callgrind-out-file=call_grind.txt ./build/dramsim3main configs/DDR4_8Gb_x8_3200.ini -c 1000050 -t extrem_trace.txt
# cd ../gprof2dot
# python gprof2dot.py -f callgrind  -s ../DRAMsim3_cmd_v4/call_grind.txt > out.dot
# dot -Tpng out.dot -o call_grind_out.png
# mv call_grind_out.png ../DRAMsim3_cmd_v4/
# cd ../DRAMsim3_cmd_v4/


valgrind --tool=callgrind --trace-children=yes --callgrind-out-file=call_grind.txt ./sa ./resource/benchmark/paper_example.kiss
cd ./gprof2dot
python gprof2dot.py -f callgrind  -s ../call_grind.txt > out.dot
dot -Tpng out.dot -o call_grind_out.png
# cp call_grind_out.png ..//dramsim3_cmd_based/cmd_call_grind_out.png
# cd ../DRAMSim3_cmd_gitlab/dramsim3_cmd_based/

valgrind --tool=callgrind --trace-children=yes --callgrind-out-file=call_grind.txt ./sa ./resource/benchmark/paper_example.kiss
cd ./gprof2dot
python gprof2dot.py -f callgrind  -s ../call_grind.txt > out.dot
dot -Tpng out.dot -o call_grind_out.png
# cp call_grind_out.png ../DRAMSim3_cmd_gitlab/dramsim3_cmd_based/cycle_call_grind_out.png
# cd ../DRAMSim3_cmd_gitlab/dramsim3_cmd_based/