#include <iostream>
#include "include/lab1.hpp"

int main()
{
    int upSpeed, downSpeed, desiredHeight;
    
    std::cout << "Enter upSpeed: ";
    std::cin >> upSpeed;

    std::cout << "Enter downSpeed: ";
    std::cin >> downSpeed;

    std::cout << "Enter desiredHeight: ";
    std::cin >> desiredHeight;

    std::cout << "Answer: " << lab1_var17(upSpeed, downSpeed, desiredHeight) << std::endl;

    return 0;
}
