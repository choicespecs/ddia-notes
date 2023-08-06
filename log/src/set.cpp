#include <iostream>
#include <fstream>
#include <string_view>

const std::string DATABASE_FILE = "database.txt";

int initial_setup(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Invalid arguments provided: set [KEY] [VALUE]" << std::endl;
        return 1;
    }

    std::ifstream infile(DATABASE_FILE);
    if (!infile)
    {
        std::cout << "Error accessing database" << std::endl;
        return 1;
    }
    infile.close();
    return 0;
}

/*
 * We can see writing to the log is only appending to the database.
 * Most efficient performance only dealing with O(1) at end.
 * This also means that you can end up with duplicate copies of keys
 * Previous keys will not be deleted or removed so can end up with inflated memory.
 */

int write(const std::string key, const std::string value)
{
    std::ofstream outfile(DATABASE_FILE, std::ios::app);
    if (!outfile)
    {
        std::cout << "Error writing to database" << std::endl;
        return 1;
    }
    outfile << key << " " << value << std::endl;
    outfile.close();
    return 0;
}

int main(int argc, char *argv[]) 
{
    if (initial_setup(argc, argv) == 1) 
    {
        exit(1);
    }

    std::string key = argv[1];
    std::string value = argv[2];

    if (write(key, value) == 1) 
    {
        exit(1);
    }

    return 0;
}
