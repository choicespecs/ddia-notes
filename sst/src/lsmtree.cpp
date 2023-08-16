#include "lsmtree.h"

static const size_t MEMTABLES_THRESHOLD = 1000;

LSMT::LSMT(size_t maxSparseIndexSize)
{
    memTables.emplace_back(maxSparseIndexSize);
}

void LSMT::insert(const std::string key, const std::string value)
{
    memTables.back().insert(key, value);

    if (memTables.back().size() >= MEMTABLES_THRESHOLD)
    {
        diskTables.push_back(memTables.back());
        memTables.pop_back();
        memTables.emplace_back(diskTables.front().maxSparseIndexSize);
        compact();
    }
}

std::string LSMT::get(const std::string key)
{
    for (auto it = memTables.rbegin(); it != memTables.rend(); ++it)
    {
        const std::string value = it->get(key);
        if (!value.empty())
            return value;
    }

    for (auto table : diskTables)
    {
        const std::string value = table.get(key);
        if (!value.empty())
            return value;
    }

    return "";
}

void LSMT::compact() 
{
    std::map<std::string, std::string> compactedData;

    for (const SSTable table : diskTables)
    {
        for (const auto entry : table)
            compactedData[entry.first] = entry.second;
    }

    SSTable compactedTable(diskTables.front().maxSparseIndexSize);
    for (const auto entry : compactedData)
        compactedTable.insert(entry.first, entry.second);

    diskTables.clear();
    diskTables.push_back(compactedTable);
}
