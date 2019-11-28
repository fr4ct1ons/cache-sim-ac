#include"../include/core.h"

namespace memsim
{
    
    core::core(size_t cacheSize)
    {
        cacheL1 = new int[cacheSize];
    }

} // namespace memsim
