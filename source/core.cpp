#include"../include/core.h"
#include<iostream>

namespace memsim
{
    
    core::core(size_t newCacheSize)
    {
        cacheL1 = new memVal[newCacheSize];
        cacheSize = newCacheSize;
    }
    void core::setVal(int address, int val)
    {
        cacheL1[address].val = val;
    }

    void core::writeVal(memVal &value)
    {
        if(currentAddress >= cacheSize)
        {
            std::cout << "ERROR - Cache memory full!" << std::endl;
            return;
        }

        cacheL1[currentAddress].val = value.val;
        cacheL1[currentAddress].l2Ref = value.l2Ref;
        cacheL1[currentAddress].mmRef = value.mmRef;
        cacheL1[currentAddress].l1Ref = &cacheL1[currentAddress];
        value.l1Ref = &cacheL1[currentAddress];
        currentAddress++;

        if(currentAddress >= cacheSize)
        {
            std::cout << "Attention - Cache memory now full!" << std::endl;
        }
    }

    void core::updateValL1(int index, int &newVal)
    {
        if(index >= currentAddress)
        {
            std::cout << "INVALID ADDRESS - This address has not been initialized yet. Number of initialized addresses: " << currentAddress << std::endl;
        return;
        }
        std::cout << "WRITING CACHEL1" << std::endl;
        cacheL1[index].val = newVal;
        std::cout << "WRITING MEMORY" << std::endl;
        *(cacheL1[index].mmRef) = newVal;
        std::cout << "WRITING CACHEL2" << std::endl;
        cacheL1[index].l2Ref->val = newVal;
    }

} // namespace memsim
