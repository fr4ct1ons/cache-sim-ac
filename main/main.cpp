#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include"../include/processor.h"
#include"../include/commands.h"

// Splits a string s, based on the caracter c.
std::vector<std::string> split(const std::string& s, const char& c)
{
	std::string buff{""};
	std::vector<std::string> v;
	
	for(auto n:s)
	{
		if(n != c) 
            buff+=n; 
        else if(n == c && buff != "")
        { 
            v.push_back(buff); 
            buff = ""; 
        }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}

// ./cachesim.out <input file> <number of cores> <L1 size> L2 size>
int main(int argc, char const *argv[])
{
    std::vector<int> mainMemory = std::vector<int>();
    std::vector<memsim::processor> processors;

    if(argc == 4)
    {
        int L1Size, numOfCores;
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
                processors[i] = memsim::processor(L1Size * 2, L1Size);
            }
            std::cout << "Finished building class!" << std::endl;
        }

        std::ifstream file(argv[1]);
        if(!file)
        {
            std::cerr << "ERROR - Could not open file." << std::endl;
            std::exit(1);
        }

        int bufferVal;
        while(!file.eof())
        {
            file >> bufferVal;
            mainMemory.push_back(bufferVal);
        }
    }
    else if(argc == 2)
    {
        if(argv[1] == "-h" || "-help")
        std::cout << "Usage: ./cachesim.out <input file> <number of cores> <L1 size> L2 size>" << std::endl;
        exit(0);
    }
    else
    {
        std::cout << "TODO: Add interface for if the user does not run the program using argv \n"
                  << "Usage: ./cachesim.out <input file> <number of cores> <L1 size> L2 size>" << std::endl;
        exit(0);
    }

    bool canRun = true;
    int operation;

    while(canRun)
    {
        std::cout << "\nWhat do you want to do next?\n" 
                  << "0 - Exit the program. \n"
                  << "1 - Print a value from an address in the main memory.\n" 
                  << "2 - Write a value from the main memory into the cache. \n" 
                  << "3 - Update a value in the memory.\n" 
                  << "4 - Insert a new value in the main memory.\n" 
                  << "5 - Get the system info."<< std::endl;

        std::cin >> operation;

        if(operation == EXIT)
            exit(0);
        else if(operation == PRINT)
        {
            int address;
            std::cout << "Understood, please insert the adress you want to read from, from 0 to " << mainMemory.size() - 1 << "." << std::endl;
            std::cin >> address;
            std::cout << "Value: " << mainMemory[address] << std::endl;
        }
        else if(operation == STORE_CACHE)
        {
            int address, coreNum, tempCore;
            std::cout << "Understood, please insert the adress you want to store, from 0 to " << mainMemory.size() - 1 << "." << std::endl;
            std::cin >> address;
            std::cout << "Value to be stored: " << mainMemory[address] << "\n"
                      << "Now, please insert the core you want to store the value at, from 1 to " << processors.size() * 2 << "." << std::endl;
            std::cin >> coreNum;
            tempCore = coreNum;

            while(coreNum > 2)
                coreNum -= 2;
            
            processors[std::ceil( ((float)tempCore) /2 ) - 1].writeVal(mainMemory[address], coreNum);
            
        }
        else if(operation == UPDATE_CACHEL1)
        {
            int address, coreNum, tempCore, value;
            std::cout << "Understood, please insert the number of the core you want to access, from 1 to " << (processors.size() * 2) << "." << std::endl;
            std::cin >> coreNum;
            std::cout << "Now, please insert the index of the L1 cache of the same core, from 0 to " << (processors[0].getL2Size()/2) - 1 << "." << std::endl;
            std::cin >> address;
            std::cout << "Finally, please insert the value you want to store." << std::endl;
            std::cin >> value;

            tempCore = coreNum;

            while(coreNum > 2)
                coreNum -= 2;
            
            processors[std::ceil( ((float)tempCore) /2 ) - 1].updateValL1(value, coreNum, address);
        }
        else if(operation == ADD_MAINMEMORY_VAL)
        {
            int value;
            std::cout << "Understood, please insert the value you want to add to the main memory." << std::endl;
            std::cin >> value;
            mainMemory.push_back(value);
            std::cout << "Inserted " << value << " at the end of the system memory." << std::endl;
        }
        else if(operation == GET_SYSINFO)
        {
            std::cout << "Number of elements in the main memory: " << mainMemory.size() << std::endl;
            std::cout << "Elements: " << std::endl;
            for(int v : mainMemory)
            {
                std::cout << v << " - ";
            }
            std::cout << std::endl;

            int coreNum = 1;
            for(memsim::processor proc : processors)
            {
                std::cout << "Values inside L2 of processor " << (coreNum + 1) / 2 << ":\n" << proc <<  std::endl;

                std::cout << "Current L1 address of core " << coreNum << ": " << proc.numOfElementsCache(1) << "/" << (proc.getL2Size()/2) - 1 << std::endl;
                std::cout << "Values inside L1 of core " << coreNum << ":\n" << proc.getCore(1) << std::endl;
                coreNum++;

                std::cout << "Current L1 address of core " << coreNum << ": " << proc.numOfElementsCache(2) << "/" << (proc.getL2Size()/2) - 1<< std::endl;
                std::cout << "Values inside L1 of core " << coreNum << ":\n" << proc.getCore(2) << "\n" << std::endl;
                coreNum++;        
            }
        }
    }
    
    return 0;
}