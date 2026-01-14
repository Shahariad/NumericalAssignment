 Heat Equation Solver

This project implements the Heat equation using two numerical methods:  

- Crank–Nicolson (CN) – implicit, unconditionally stable  
- Forward-Time Central-Space (FTCS) – explicit, conditionally stable  

The goal is to compute temperature distribution along a rod over time and compare accuracy and stability of the two methods.


Project Files

- `heat_compare.c` → C program to compute CN and FTCS solutions  
- `cn_solution.csv` → CN solution output  
- `ftcs_solution.csv` → FTCS solution output  
- `error.csv` → Absolute error |CN - FTCS|  
- `PlotResults.java` → Java program to plot CN vs FTCS and error  
- `README.md` → This file  



Summary

- CN is more accurate and stable compared to FTCS.  
- FTCS is simpler but requires small time steps for stability.  
- Error analysis confirms the advantage of CN.  
- The project demonstrates numerical solution, visualization, and method comparison.

---



- Md Shahariad Islam  
- Course: Numerical Methods  
- Assignment: 1D Heat Equation

