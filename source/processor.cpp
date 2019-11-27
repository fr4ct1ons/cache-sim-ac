#include"../include/processor.h"

namespace memsim
{
    
    processor::processor(size_t cacheSize = DEFAULT_L2_SIZE)
    {
        cacheL2 = new int[cacheSize];
    }

} // namespace memsim
