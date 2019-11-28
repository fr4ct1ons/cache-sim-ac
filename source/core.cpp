#include"../include/core.h"

namespace memsim
{
    
    core::core(size_t cacheSize)
    {
        cacheL1 = new int[cacheSize];
    }
    void core::setVal(int address, int val)
    {
        cacheL1[address] = val;
    }

} // namespace memsim
