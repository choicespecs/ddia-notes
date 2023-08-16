#include "lsmtree.h"
#include <iostream>

int main()
{
    LSMT* lsmTree = new LSMT(100);
    
    while (true)
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
            lsmTree->insert(key, value);
        } 
        else if (command == "get")
        {
            std::string key;
            std::cout << "Enter a key to search for: ";
            std::cin >> key;
            std::string value = lsmTree->get(key);
            if (value.empty())
                std::cout << "Key not found." << std::endl;
            else
                std::cout << value << std::endl;
        }
        else 
        {
            std::cout << "Invalid command." << std::endl;
        }
    }
    return 0;
}
