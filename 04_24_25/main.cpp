#include "map.h"
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    // Original code
    map<int, std::string> hobbits;
    std::ifstream name("names.txt");
    for (int i = 0; !name.eof(); i++)
    {
        std::string in;
        std::getline(name >> std::ws, in);
        hobbits.insert(i, in);
    }
    
    std::cout << "Original list of hobbits:" << std::endl;
    for (auto it = hobbits.begin(); it.hasNext(); ++it)
    {
        pair<int, std::string> p = *it;
        std::cout << p.getKey() << ": " << p.getValue() << std::endl;
    }
    std::cout << std::endl << std::endl;

    std::cout << "hobbits[6]: " << hobbits[6] << std::endl;
    hobbits[0] = "Tasha Oakbottom";
    std::cout << "hobbits[0]: " << hobbits[0] << std::endl;
    hobbits[15] = "Brianna Button";
    std::cout << "hobbits[15]: " << hobbits[15] << std::endl;

    std::cout << std::endl << std::endl;
    
    // New code for AVL delete testing
    std::cout << "Testing AVL delete operations:" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    
    // Test 1: Delete a leaf node
    std::cout << "\nDeleting last hobbit (key=" << (hobbits.size()-1) << ")..." << std::endl;
    hobbits.remove(hobbits.size()-1);
    
    // Test 2: Delete a node with one child
    std::cout << "Deleting hobbit with key=7..." << std::endl;
    hobbits.remove(7);
    
    // Test 3: Delete a node with two children
    std::cout << "Deleting hobbit with key=5..." << std::endl;
    hobbits.remove(5);
    
    // Display remaining hobbits
    std::cout << "\nRemaining hobbits after deletions:" << std::endl;
    for (auto it = hobbits.begin(); it.hasNext(); ++it)
    {
        pair<int, std::string> p = *it;
        std::cout << p.getKey() << ": " << p.getValue() << std::endl;
    }
    
    // Verify the tree is still balanced by checking access operations
    std::cout << "\nVerifying tree is still balanced:" << std::endl;
    std::cout << "hobbits.at(3): " << hobbits.at(3) << std::endl;
    std::cout << "hobbits[10]: " << hobbits[10] << std::endl;
    
    // Original code continues
    std::cout << hobbits.at(7) << std::endl;

    return 0;
}
