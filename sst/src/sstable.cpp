#include <iostream> 
#include <fstream> 
#include "sstable.h" 
#include <sys/stat.h>
const std::string CACHE1_FILENAME = "./data/cache1.txt"; 
const std::string CACHE2_FILENAME = "./data/cache2.txt";
const size_t SSTable::MAX_CACHE_SIZE = 1000;

SSTable::SSTable(size_t indexSize) : maxSparseIndexSize(indexSize)
{ 
    loadCacheFromFile(CACHE1_FILENAME, sparseIndex);
    struct stat buffer;
    if (stat(CACHE1_FILENAME.c_str(), &buffer) == 0)
        cache1File = new std::ofstream(CACHE1_FILENAME, std::ios::app);
    else
        cache1File = new std::ofstream(CACHE1_FILENAME);
    cache2File = new std::ofstream(CACHE2_FILENAME);
}

SSTable::~SSTable()
{
    cache1File->close();
    cache2File->close();
}

size_t SSTable::size() const
{
    return data.size();
}

void SSTable::loadCacheFromFile(const std::string filename, std::map<std::string, std::string>& dataMap)
{
    std::cout << "Loading cache from file." << std::endl;
    std::ifstream cacheFile;
    cacheFile.open(CACHE1_FILENAME, std::ios::in);
    if (cacheFile.is_open()) 
    {
        std::cout << "cache file is open." << std::endl;
        std::string line;
        while (std::getline(cacheFile, line))
        {
            size_t delimiterPos = line.find(' ');
            if (delimiterPos != std::string::npos)
            {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                dataMap[key] = value;
            }
        }
        cacheFile.close();
    }
}

size_t SSTable::getFileSize(const std::string filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open())
        return 0;
    return static_cast<size_t>(file.tellg());
}

void SSTable::insert(const std::string key, const std::string value)
{
    tree.insert(key, value);
    updateSparseIndex(key, value);

    if (getFileSize(CACHE1_FILENAME) < MAX_CACHE_SIZE)
        writeToCache(CACHE1_FILENAME, key, value);
    else if (getFileSize(CACHE2_FILENAME) < MAX_CACHE_SIZE)
        writeToCache(CACHE2_FILENAME, key, value);
    else
    {
        compact();
        writeToCache(CACHE1_FILENAME, key, value);
    }
}

void SSTable::writeToCache(const std::string filename, const std::string key, const std::string value)
{
    std::cout << "Writing to Cache" << std::endl;
    if (filename == CACHE1_FILENAME && cache1File->is_open())
        *cache1File << key << " " << value << std::endl;
    else if (filename == CACHE2_FILENAME && cache2File->is_open())
        *cache2File << key << " " << value << std::endl;
}

const std::string SSTable::getSmallerValue(const std::string key) const
{
    auto it = sparseIndex.upper_bound(key);
    if (it != sparseIndex.begin())
    {
        --it;
        return tree.getSmallerValue(it->first);
    }

    return "No smaller value found.";
}

std::string SSTable::get(const std::string key)
{
    auto it = sparseIndex.find(key);
    if (it != sparseIndex.end())
        return it->second;

    std::string smallerValue = getSmallerValue(key);

    if (smallerValue != "No smaller value found.")
    {
        std::string value = tree.getValue(key);
        updateSparseIndex(key, value);
        return value;
    }

    return "Key not found";
}

void SSTable::updateSparseIndex(const std::string key, const std::string value)
{
    sparseIndex[key] = value;

    if (sparseIndex.size() > maxSparseIndexSize && !sparseIndex.empty())
        sparseIndex.erase(sparseIndex.begin());
}

void SSTable::compact()
{
    std::ifstream cache2(CACHE2_FILENAME);

    std::map<std::string, std::string> compactedData;

    loadCacheFromFile(CACHE1_FILENAME, compactedData);

    std::string key, value;
    while (cache2 >> key >> value)
        compactedData[key] = value;

    cache2.close();

    cache2File->close();
    cache2File->open(CACHE2_FILENAME, std::ios::trunc);

    cache1File->close();
    cache1File->open(CACHE1_FILENAME, std::ios::trunc);

    for (const auto entry : compactedData)
        *cache1File << entry.first <<  " " << entry.second << std::endl;

    loadCacheFromFile(CACHE1_FILENAME, sparseIndex);
}


