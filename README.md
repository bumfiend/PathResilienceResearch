# PathResilienceResearch

# Introduction

  The purpose of this project is to test the soft error resilience of various graph traversal and pathfind algorithms. This repository supplies all the code needed to run LLFI and replicate the expirements from my paper.
  
# Requirements

  1. Have LLFI installed
  2. Clang v3.4
  3. Python 3 and above

# How to Run

First choose the directory you would like to test, there are four algorithm to expirement with.

1. Compile sqrt.c to readable IR:
    clang -emit-llvm -S *.c
2. Instrument IR-level codes to readable IR:
    instrument --readable sqrt.ll
3. Profile: run a fault-free IR:
    profile ./llfi/sqrt-profiling.exe
4. Fault Injection: run a fault-injected IR:
    injectfault ./llfi/sqrt-faultinjection.exe
5. Analyze FI results:
    python3 measure.py
    
    
