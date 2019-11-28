#include"../include/processor.h"

namespace memsim
{
    
    processor::processor(size_t L2CacheSize, size_t L1CacheSize)
    {
        L2Size = L2CacheSize;
        cacheL2 = new int[L2CacheSize];
        cores[0] = core(L1CacheSize);
        cores[1] = core(L1CacheSize);
    }

    int processor::getL2Size() { return L2Size; }

    void processor::writeL1(int coreNum, int address, int val)
    {
        cores[coreNum].setVal(address, val);
    }

} // namespace memsim
