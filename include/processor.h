#pragma once

#include<string>
#include"core.h"

namespace memsim
{

    class processor
    {
        private:
        static const size_t DEFAULT_L2_SIZE = 200;
        int *cacheL2;

        public:
        processor(size_t);
    };

}
