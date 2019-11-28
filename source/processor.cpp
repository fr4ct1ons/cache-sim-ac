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

} // namespace memsim
