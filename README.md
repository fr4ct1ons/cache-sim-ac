# cache-sim-ac
A simulator of memory hierarchy in a multicore processor.

## Installation
Assuming you have the G++ compiler installed, just type `make` on the terminal in the folder containing this readme file. Afterwards, you can type make clean to remove the unecessary .o files.

## Usage
You can run the program by typing cachesim in the terminal. Alternatively, you can run like:
`./cachesim <inputfile> <number of cores> <L1 cache size> <L2 cache size>`
in order to automatically open the file, set the number of cores (NOTE: the number of cores MUST be divisible by two and larger than zero) set the L1 cache size and set the L2 cache size.

## Input file [WIP]

The input file must contain the data to be set up in the simulator. For example, assuming you set up the program with 4 cores, an L1 cache of 3 numbers and an L2 cache of 6 numbers, the input can be something like this:
```
# lines starting with a #, like this one will be skipped
# WRITE_L1 <core number> <address, starting at 0> <value, must be integer>
WRITE_L1 2 0 300 # will write the value 300 in the address 0 of the L1 cache of core number 2
WRITE_L1 3 2 25 # will write the value 25 in the address 2 of the L1 cache of core number 3
WRITE_L1 1 3 25 # will return an error or crash the simulation, since the L1 cache can hold 3 integers and you're trying to access a 4th one, as addresses start at 0
```

## Contact

You can contact me at https://twitter.com/fr4ct1ons or via https://github.com/lucena-fr4ct1ons/. Also, check out my other work!
