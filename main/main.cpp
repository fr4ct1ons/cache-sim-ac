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

        /*while(std::getline(file, buffer))
        {
            std::vector<std::string> words = split(buffer, ' ');
            if(words.empty())
            {
                std::cout << "Empty line" << std::endl;
                continue;
            }
            else
            {
                if(words[0][0] == '#')
                {
                    std::cout << "Skipping line." << std::endl;
                    continue;
                }
                else if(words[0] == "WRITE_L1")
                {
                    int address, value, coreNum;
                    try
                    {
                        coreNum = std::stoi(words[1]);
                        address = std::stoi(words[2]);
                        value = std::stoi(words[3]);
                    }
                    catch(std::exception& e)
                    {
                        std::cerr << "ERROR on line: ";
                        for(auto val: words)
                            std::cerr << val << " ";
                        std::cerr <<  e.what() << std::endl;
                    }
                    
                    int tempCore = coreNum;

                    while(coreNum > 2)
                        coreNum -= 2;

                    processors[std::ceil( ((float)tempCore) /2 ) - 1].writeL1(coreNum - 1, address, value);
                    
                    std::cout << "WRITING VALUE " << value << " TO L1 OF CORE NUMBER " << coreNum << " OF PROCESSOR " << std::ceil(((float)tempCore)/2) << std::endl;

                    //processors[std::ceil(tempVal/2)];
                    
                }
            }
        }*/

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
        std::cout << "What do you want to do next?\n" 
                  << "0 - Exit the program. \n"
                  << "1 - Print a value from an address in the main memory.\n" 
                  << "2 - Write a value from the main memory into the cache." << std::endl;

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
                      << "Now, please insert the core you want to store the value at. " << std::endl;
            std::cin >> coreNum;
            tempCore = coreNum;

            while(coreNum > 2)
                coreNum -= 2;
            
            processors[std::ceil( ((float)tempCore) /2 ) - 1].writeVal(mainMemory[address], coreNum);
            
        }
    }
    
    return 0;
}