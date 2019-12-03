# cache-sim-ac
A simulator of memory hierarchy in a multicore processor.  
Author: Gabriel Lucena (fr4ct1ons, lucena-fr4ct1ons)  
PT-BR: Uma tradução deste readme para PT-BR pode ser encontrado no arquivo README_PTBR.md.

## Installation
Assuming you have the G++ compiler installed, just type `make` on the terminal in the folder containing this readme file. Afterwards, you can type `make clean` to remove the unecessary .o files. Alternatively, you can type `g++ main/main.cpp source/core.cpp source/processor.cpp -I include/ -o cachesim.out` to achieve a similar effect.

## Usage
You can run the program by typing the following command in the project's root:  
`./cachesim <inputfile> <number of cores> <L1 cache size>`  
The input file must contain only numbers, which are the values to be loaded in the main memory. The number of cores must be divisible by 2. The L1 cache can be any value higher than 0. Afterwards, if the initialization is successful, you can run the program like normal.

## Project structure
The project is being developed in the C++ language.  
The project structure is as follows:  
include/ - Folder containing header files. Files containing the declaration of structs, classes etc must go in here.  
source/ - Must contain the implementations of the classes defined before, except for any template classes. They must go in the include folder.  
main/ - Must contain any file with a `main()` method.  

## Contact
For any questions, you can contact me at https://twitter.com/fr4ct1ons or via https://github.com/lucena-fr4ct1ons/. Also, check out my other work!
