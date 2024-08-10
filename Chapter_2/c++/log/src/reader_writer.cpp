#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <sys/stat.h>
#include <map>
#include <algorithm>
#include <sstream>

const std::string CACHE_1_PATH = "./data/cache-1.txt";
const std::string CACHE_2_PATH = "./data/cache-2.txt";
const std::string DATABASE_PATH = "database.txt";
const std::size_t MAX_CACHE_SIZE = 1000;

std::ofstream cache1;
std::ofstream cache2;
std::ofstream database;
std::unordered_map<std::string, std::string> cache;

long long file_size(const std::string filename)
{
    struct stat buffer;
    if (stat(filename.c_str(), &buffer) == 0)
        return static_cast<long long>(buffer.st_size);
    return -1;
}

bool file_exists(const std::string file_name)
{
    struct stat buffer;
    return (stat(file_name.c_str(), &buffer) == 0);
}

void initial_startup()
{
    if (file_exists(CACHE_1_PATH))
    {
        std::ifstream prev_cache(CACHE_1_PATH);
        if (prev_cache)
        {
            std::string key, value;
            while (prev_cache >> key >> value)
                cache[key] = value;

            prev_cache.close();
        }
        cache1.open(CACHE_1_PATH, std::ios::app);
    }
    else
        cache1.open(CACHE_1_PATH);

    cache2.open(CACHE_2_PATH);

    if (file_exists(DATABASE_PATH))
        database.open(DATABASE_PATH, std::ios::app);
    else
        database.open(DATABASE_PATH);
}

void close_streams() 
{
    database.close();
    cache1.close();
    cache2.close();
}

void compact_cache()
{
    cache1.close();
    cache2.close();
    
    std::ifstream cache1_read(CACHE_2_PATH);
    std::ifstream cache2_read(CACHE_2_PATH);

    if (!cache2_read || !cache1)
    {
        std::cerr << "Error opening cache files for compaction." << std::endl;
        return;
    }

    std::map<std::string, std::string> latest_values;
    std::string line;
    while (std::getline(cache1_read, line))
    {
        std::istringstream iss(line);
        std::string key, value;
        iss >> key >> value;
        latest_values[key] = value;
    }

    while (std::getline(cache2_read, line))
    {
        std::istringstream iss(line);
        std::string key, value;
        iss >> key >> value;
        latest_values[key] = value;
    }

    cache1.open(CACHE_1_PATH, std::ios::out | std::ios::trunc);
    for (const auto key : latest_values)
        cache1 << key.first << " " << key.second << std::endl;
    cache1.close();

    cache1_read.close();
    cache2_read.close();

    cache2.open(CACHE_2_PATH, std::ios::out | std::ios::trunc);
    cache2.close();

    cache1.open(CACHE_1_PATH, std::ios::out | std::ios::app);
    cache2.open(CACHE_2_PATH, std::ios::out | std::ios::app);
}

void write_to_cache(const std::string key, const std::string value)
{
    std::ofstream current_cache;

    if (std::ifstream(CACHE_1_PATH).tellg() >= MAX_CACHE_SIZE)
        current_cache.open(CACHE_2_PATH, std::ios::app);
    else
        current_cache.open(CACHE_1_PATH, std::ios::app);

    current_cache << key << " " << value << std::endl;
    current_cache.close();

    if (cache2.tellp() >= MAX_CACHE_SIZE)
        compact_cache();
}

void write(const std::string key, const std::string value)
{
    write_to_cache(key, value);
    database << key << " " << value << std::endl;
    cache[key] = value;
}

std::string find_cache(const std::string key) 
{
    auto cache_iter = cache.find(key);
    if (cache_iter != cache.end())
        return cache_iter->second;
    return "";
}

std::string find_database(const std::string key)
{
    std::ifstream read_database(DATABASE_PATH);
    if (!read_database)
    {
        std::cerr << "Error: cannot open database for reading." << std::endl;
        return "";
    }
    std::string line, value;
    while (std::getline(read_database, line))
    {
        size_t pos = line.find(key);
        if (pos != std::string::npos)
        {
            value = line.substr(pos + key.size() + 1);
            return value;
        }
    }
    return "";
}

int main()
{
    initial_startup();

    while(true)
    {
        std::string command;
        std::cout << "Enter a command (insert, get, exit): ";
        std::cin >> command;
        if (command == "exit")
            break;
        else if (command == "insert")
        {
            std::string key, value;
            std::cout << "Enter a key: ";
            std::cin >> key;
            std::cout << "Enter the value: ";
            std::cin >> value;
            write(key, value);
        }
        else if (command == "get")
        {
            std::string key;
            std::cout << "Enter a key to search for: ";
            std::cin >> key;
            std::string value = find_cache(key);
            if (value.empty())
                value = find_database(key);
            if (value.empty())
                std::cout << "Key not found in cache or data file." << std::endl;
            if (!value.empty())
                std::cout << value << std::endl;
        }
        else
        {
            std::cout << "Invalid command." << std::endl;
        }
    }
    close_streams();
    return 0;
}


