#!/bin/bash

mkdir -p logs;

make vector;
./ft_exec_vector > ./logs/ft_exec_vector.log;
make std-vector;
./std_exec_vector > ./logs/std_exec_vector.log;
diff ./logs/ft_exec_vector.log ./logs/std_exec_vector.log > ./logs/trace_vector;
more ./logs/trace_vector
