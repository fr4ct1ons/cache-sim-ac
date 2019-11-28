#pragma once

#include<string>

namespace memsim
{

    class core
    {
        private:
        int *cacheL1;

        public:
        core(size_t cacheSize = DEFAULT_L1_SIZE);
        static const size_t DEFAULT_L1_SIZE = 30;
    };

}