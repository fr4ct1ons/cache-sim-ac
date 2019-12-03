#include"../include/processor.h"
#include<iostream>

namespace memsim
{
    
    processor::processor(size_t L2CacheSize, size_t L1CacheSize)
    {
        L2Size = L2CacheSize;
        cacheL2 = new memVal[L2CacheSize];
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

    void processor::writeVal(int &value, int coreNum)
    {
        if(coreNum == 1)
        {
            cacheL2[currentCacheAddress1].val = value;
            cacheL2[currentCacheAddress1].mmRef = &value;
            cacheL2[currentCacheAddress1].l2Ref = &cacheL2[currentCacheAddress1];
            cores[0].writeVal(cacheL2[currentCacheAddress1]);
            currentCacheAddress1++;
            if(currentCacheAddress1 >= L2Size/2)
                currentCacheAddress1 = 0;
        }
        else if(coreNum == 2)
        {
            cacheL2[currentCacheAddress2].val = value;
            cacheL2[currentCacheAddress2].mmRef = &value;
            cacheL2[currentCacheAddress2].l2Ref = &cacheL2[currentCacheAddress2];
            cores[1].writeVal(cacheL2[currentCacheAddress2]);
            currentCacheAddress2++;
            if(currentCacheAddress2 >= L2Size)
                currentCacheAddress2 >= L2Size/2;
        }
        else
        {
            std::cerr << "UNEXPECTED ERROR - Contact the program's creator at twitter.com/fr4ct1ons. " << std::endl;
        }
    }

    void processor::updateValL1(int &newVal, int coreNum, int l1Index)
    {
        cores[coreNum - 1].updateValL1(l1Index, newVal);
    }

    int processor::numOfElementsCache(int coreNum)
    {
        if(coreNum == 1)
            return currentCacheAddress1;
        else if(coreNum == 2)
            return currentCacheAddress2 - (L2Size/2);
    }

    core processor::getCore(int coreNum)
    {
        if(coreNum == 1)
            return cores[0];
        else if(coreNum == 2)
            return cores[1];
        
        return cores[0];
    }

    std::ostream& operator<<(std::ostream& os, processor &proc)
    {
        os << "{ ";
        for (int i = 0; i < proc.L2Size - 1; i++)
        {
            os << proc.cacheL2[i].val << " - ";
        }
        os << proc.cacheL2[proc.L2Size - 1].val << " }";
        return os;
    }

} // namespace memsim
