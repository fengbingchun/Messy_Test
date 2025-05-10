#!/bin/sh
#
#  Run this script to build TSPSOL executable.
#
#  NOTE: you need to have GLPK properly installed.
#
gcc -O2 -otspsol main.c maxflow.c mincut.c misc.c tsplib.c -lglpk -lm
./tspsol sample.tsp
