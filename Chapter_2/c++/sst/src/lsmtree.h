#pragma once

#include <vector>
#include "sstable.h"

class LSMT
{
    private:
        std::vector<SSTable> memTables;
        std::vector<SSTable> diskTables;

    public:
        LSMT(size_t maxSparseIndexSize);
        void insert(const std::string key, const std::string value);
        std::string get(const std::string key);

    private:
        void compact();

};
