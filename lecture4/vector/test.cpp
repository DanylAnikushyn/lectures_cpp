#include "vector.h"
#include <iostream>
#include <stdexcept>

int main()
{
    Vector<int> vec1;
    for (int i = 0; i < 20; ++i)
    {
        vec1.push_back(i);
    }
    vec1.resize(25);
    for (int i = 0; i < vec1.size(); ++i)
    {
        std::cout << vec1[i] << std::endl;
    }

    Vector<int> vec2 = {20, 10, 12, 9, 32};
    std::cout << vec2.empty() << std::endl;
    vec2.clear();
    std::cout << vec2.empty() << std::endl;
    vec2 = {1, 2, 3, 4, 5};
    vec2.insert(vec2.begin() + 5, 100);
    vec2.insert(vec2.begin() + 1, 200);
    vec2.push_back(11);
    std::cout << std::endl;
    for (int i = 0; i < vec2.size(); ++i)
    {
        std::cout << vec2[i] << std::endl;
    }

    try {
        vec2.at(100);
    } 
    catch (const std::out_of_range& err)
    {
        std::cout << err.what() << std::endl;
    }

    
    return 0;
}