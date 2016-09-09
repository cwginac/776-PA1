# CS 776: Programming Assignment 1

Given two evaluation black box functions, find the optimal 100 bit binary array (int [100] where the int's are only 0 or 1).

## Installation

To compile, run the following instructions:
make 
or
make -f makefile1

## Usage

To run, run the following instruction:
./main.out

This will take a while, each thread will run 10000000 (or whatever is entered in the while loop in thread_entry) hill climbing with random starts.
