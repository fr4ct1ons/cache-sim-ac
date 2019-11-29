#pragma once

#include<string>
#include"core.h"

namespace memsim
{

    class processor
    {
        private:
        memVal *cacheL2;
        core cores[2];
        int L2Size, currentCacheAddress1 = 0, currentCacheAddress2 = 0;

        public:
        processor(size_t L2CacheSize = DEFAULT_L2_SIZE, size_t L1CacheSize = core::DEFAULT_L1_SIZE);
        static const size_t DEFAULT_L2_SIZE = 200;

        int getL2Size();
        void writeL1(int coreNum, int address, int val);
        void writeVal(int &value, int coreNum);
        void updateValL1(int &newVal, int coreNum, int l1Index);
    };

}
