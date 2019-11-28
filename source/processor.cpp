#include"../include/processor.h"
#include<iostream>

namespace memsim
{
    
    processor::processor(size_t L2CacheSize, size_t L1CacheSize)
    {
        L2Size = L2CacheSize;
        cacheL2 = new int[L2CacheSize];
        cores[0] = core(L1CacheSize);
        cores[1] = core(L1CacheSize);

        currentCacheAddress1 = 0;
        currentCacheAddress2 = L2Size/2;
    }

    int processor::getL2Size() { return L2Size; }

    void processor::writeL1(int coreNum, int address, int val)
    {
        cores[coreNum].setVal(address, val);
    }
    void processor::writeVal(int value, int coreNum)
    {
        if(coreNum == 1)
        {
            cacheL2[currentCacheAddress1] = value;
            cores[0].writeVal(value);
            currentCacheAddress1++;
        }
        else if(coreNum == 2)
        {
            cacheL2[currentCacheAddress2] = value;
            cores[1].writeVal(value);
            currentCacheAddress2++;
        }
        else
        {
            std::cerr << "UNEXPECTED ERROR - Contact the program's creator at twitter.com/fr4ct1ons. " << std::endl;
        }
    }

} // namespace memsim
