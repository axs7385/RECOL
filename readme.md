# RECOL: Graph Coloring with Reductions

This repository contains the source code and experiment results for our graph coloring study.

## Contents

- **RECOL.cpp**: Source code of our proposed algorithm **RECOL**.  
- **fastcolor/**: Directory containing the executable of the **FastColor** baseline.  
- **LS-WGCP/**: Directory containing the executable of the **LS-WGCP** baseline.  
- **planarity-cpp/**: Directory containing the executable of the **Planarity-Cpp** baseline.  
- **result/**: Experimental results of all algorithms on each dataset.  
- **graph_statistics.csv**: A CSV file summarizing the source and basic statistics of all datasets used in experiments.  
- **readme**: This file.  

## Compilation

To compile **RECOL**, run:
```bash
g++ RECOL.cpp -o RECOL -O3
