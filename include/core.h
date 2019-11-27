#pragma once

#include<string>

namespace memsim
{

    class core
    {
        private:
        static const size_t DEFAULT_L1_SIZE = 30;
        int *cacheL1;

        public:
        core(size_t);
    };

}