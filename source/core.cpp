#include"../include/core.h"

namespace memsim
{
    
    core::core(size_t cacheSize = DEFAULT_L1_SIZE)
    {
        cacheL1 = new int[cacheSize];
    }

} // namespace memsim
