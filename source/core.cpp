#include"../include/core.h"
#include<iostream>

namespace memsim
{
    
    core::core(size_t newCacheSize)
    {
        cacheL1 = new int[newCacheSize];
        cacheSize = newCacheSize;
    }
    void core::setVal(int address, int val)
    {
        cacheL1[address] = val;
    }

    void core::writeVal(int value)
    {
        if(currentAddress >= cacheSize)
        {
            std::cout << "ERROR - Cache memory full!" << std::endl;
            return;
        }
        cacheL1[currentAddress] = value;
        currentAddress++;
        if(currentAddress >= cacheSize)
        {
            std::cout << "Attention - Cache memory now full!" << std::endl;
        }
    }

} // namespace memsim
