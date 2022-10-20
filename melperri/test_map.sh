#!/bin/bash

mkdir -p logs;

make map;
./ft_exec_map > ./logs/ft_exec_map.log;
make std-map;
./std_exec_map > ./logs/std_exec_map.log;
diff ./logs/ft_exec_map.log ./logs/std_exec_map.log > ./logs/trace_map;
cat ./logs/trace_map
