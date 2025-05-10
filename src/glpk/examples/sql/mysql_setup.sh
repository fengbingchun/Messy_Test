#!/bin/sh
# This file can be used to create database glpk in MySQL.
echo MySQL is called for user root. 
mysql -f -u root -p < sudoku.sql
echo MySQL is called for user root.
mysql -f -u root -p < transp.sql
