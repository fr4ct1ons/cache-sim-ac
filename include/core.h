#pragma once

#include<string>

typedef struct memVal
{
    memVal *l1Ref, *l2Ref;
    int *mmRef;
    int val;
} memVal;

namespace memsim
{

    class core
    {
        private:
        memVal *cacheL1;
        int cacheSize, currentAddress = 0;

        public:
        core(size_t newCacheSize = DEFAULT_L1_SIZE);
        void setVal(int, int);
        static const size_t DEFAULT_L1_SIZE = 30;
        void writeVal(int value);
    };

}