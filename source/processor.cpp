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
            cacheL2[currentCacheAddress1].l2Ref = &cacheL2[currentCacheAddress2];
            cores[0].writeVal(cacheL2[currentCacheAddress1]);
            currentCacheAddress1++;
        }
        else if(coreNum == 2)
        {
            cacheL2[currentCacheAddress2].val = value;
            cacheL2[currentCacheAddress2].mmRef = &value;
            cacheL2[currentCacheAddress2].l2Ref = &cacheL2[currentCacheAddress2];
            cores[1].writeVal(cacheL2[currentCacheAddress2]);
            currentCacheAddress2++;
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

} // namespace memsim
