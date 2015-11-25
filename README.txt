README

This code is based on C++
Optimal running platform is on remote server(calculation is relatively big)
During our experiments, we use BananaPi, 2-core 1Ghz ARM7 processor

Instruction:
1. create the graph using Gephi, Pajek, GDTang, etc.
2. paste the node relations in format.xls to generate C code.
3. paste the generated C code to netdata.cpp
4. set parameters in setting.h
5. run run.bash to operate (running on multi-core processor is encouraged for faster speed)
6. after the calculation, result.csv is the output of the results, with each column the number of infected nodes using one of the four algorithm
7. using excel to make a figure to see directly

Codes of Target, acquaintance and random immunization strategy algorithm is not from the official sources, but from our "imagination", using a similar code structure and method with our algorithm. Although low in efficiency, but rather fair compared with our "in-depth" algorithm.
The fact is our algorithm does not largely lengthen the calculation time, as we can see from "run time" during the calculation.

By: Li Chen(li_chen12@fudan.edu.cn) 
2015.7