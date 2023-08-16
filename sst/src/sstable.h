#pragma once

#include <string>
#include <map>
#include <fstream>
#include "avltree.h"

class SSTable 
{

    private:
        AVLTree tree;
        std::map<std::string, std::string> sparseIndex;
        static const size_t MAX_CACHE_SIZE;

        std::ofstream* cache1File;
        std::ofstream* cache2File;

        std::map<std::string, std::string> data;

    public:
        class Iterator 
        {
            private:
                std::map<std::string, std::string>::const_iterator iter;

            public:
                Iterator(std::map<std::string, std::string>::const_iterator it)
                    : iter(it) {}

                Iterator& operator++()
                {
                    ++iter;
                    return *this;
                }

                const std::pair<const std::string, std::string>& operator*() const 
                {
                    return *iter;
                }

                bool operator==(const Iterator& other) const
                {
                    return iter == other.iter;
                }

                bool operator!=(const Iterator& other) const
                {
                    return iter != other.iter;
                }
        };

        Iterator begin() const
        {
            return Iterator(data.begin());
        }
        Iterator end() const
        {
            return Iterator(data.end());
        }
        size_t maxSparseIndexSize;

    public:
        SSTable(size_t indexSize);
        ~SSTable();

        void insert(const std::string key, const std::string value);
        std::string get(const std::string key);
        const std::string getSmallerValue(const std::string key) const;
        size_t size() const;


    private:
        void loadCacheFromFile(const std::string filename, std::map<std::string, std::string>& dataMap);
        void updateSparseIndex(const std::string key, const std::string value);
        static size_t getFileSize(const std::string filename);
        void writeToCache(const std::string filename, const std::string key, const std::string value);
        void compact();
};
