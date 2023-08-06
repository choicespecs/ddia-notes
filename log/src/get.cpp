#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const std::string DATABASE_FILE = "database.txt";

int initial_setup(int argc, char* argv[])
{
    // check arguments
    if (argc != 2)
    {
        std::cout << "Invalid arguments provided: get [KEY]" << std::endl;
        return 1;
    }

    // check if file exists
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
 * Helper function which will find the key against the first word within database.
 * This will help restrict key finding to exact match against partial matches
 * Example: 4 cannot give partial match to 45 due to being first character.
 */
bool key_found(const std::string line, const std::string key)
{
    std::istringstream iss(line);
    std::string line_key;
    iss >> line_key;
    return line_key == key;
}

/*
 * Getting from this specific database means we have to iterate through every single
 * line to determine where the key is. The most updated key / value will be found at the end.
 * This means we constantly must continue to iterate through the entire database from begining to end.
 */
int get(const std::string key)
{
    bool found = false;
    std::ifstream infile(DATABASE_FILE);

    std::string line, result;

    while(std::getline(infile, line)) 
    {
        if (key_found(line, key))
        {
            // remove key from line;
            line.erase(0, key.size() + 1);
            result = line;
            found = true;
        }
    }

    infile.close();
    
    if (found)
        std::cout << result << std::endl;
    else
        std::cout << "Key not found." << std::endl;
    
    return 0;
}

int main(int argc, char* argv[])
{
    if (initial_setup(argc, argv) == 1) 
    {
        exit(1);
    }

    std::string key = argv[1];

    get(key);

    return 0;
}
