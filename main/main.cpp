#include<iostream>
#include<vector>
#include"../include/processor.h"


// ./cachesim.out <input file> <number of cores> <L1 size> L2 size>
int main(int argc, char const *argv[])
{

    std::vector<memsim::processor> processors;

    if(argc == 5)
    {
        int L1Size, L2Size, numOfCores;
        // Try-catch block for getting the L1Size, L2Size and numOfCores size.
        {
            try
            {
                numOfCores = std::stoi(argv[2]);
            }
            catch(std::invalid_argument e)
            {
                std::cerr << "ERROR - Invalid value for the number of cores. Please insert a number only, no text." << std::endl;
                exit(1);
            }
            try
            {
                L1Size = std::stoi(argv[3]);
            }
            catch(std::invalid_argument e)
            {
                std::cerr << "ERROR - Invalid value for the L1 Cache size. Please insert a number only, no text." << std::endl;
                exit(1);
            }
            try
            {
                L2Size = std::stoi(argv[4]);
            }
            catch(std::invalid_argument e)
            {
                std::cerr << "ERROR - Invalid value for the L2 Cache size. Please insert a number only, no text." << std::endl;
                exit(1);
            } 
        }

        if(numOfCores == 0 || numOfCores % 2 != 0)
        {
            std::cerr << "ERROR - The number of cores must be a multiple of two or different than 0. You inserted " << numOfCores << "." << std::endl;
            exit(1);
        }
        else
        {
            processors = std::vector<memsim::processor>(numOfCores / 2);
            for (size_t i = 0; i < processors.size(); i++)
            {
                processors[i] = memsim::processor(L2Size, L1Size);
            }
            std::cout << "Finished building class!" << std::endl;
        }
        std::cout << processors[0].getL2Size() << std::endl;
    }
    else
    {
        std::cout << "TODO: Add interface for if the user does not run the program using argv" << std::endl;
    }
    
    return 0;
}