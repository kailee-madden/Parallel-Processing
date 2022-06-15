# README

- Each BFS implementation has its own directory containing the graphProperties files and the testGraphs file
- Each OpenMP implementation has subdirectories containing the output files for each of the 5 test cases.
- Each OpenMP implementation has a subdirectory containing the sbatch scripts for 1-128 threads. The names of the output files from these scripts have to be modified depending on the test case, but otherwise nothing needs to be changed for different runs.

### Requirements
- C++11 or higher
- OpenMP

### Instructions for Compiling
Use c++11 when compiling: 'clang++ -fopenmp -std=c++11 graphProperties.cpp OMP1.cpp -o BFS1exe'

### Running
- Run using the sbatch files, ensuring that the compiled output file is correctly named in the sbatch file
- Or run using a designated node and on that node include the following modules:
    - slurm
    - cpu
    - aocc
