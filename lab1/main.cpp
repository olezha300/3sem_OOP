#include <iostream>
#include "src/lab1.cpp"

int main()
{
    long long upSpeed, downSpeed, desiredHeight;
    
    std::cout << "Enter upSpeed: ";
    std::cin >> upSpeed;

    std::cout << "Enter downSpeed: ";
    std::cin >> downSpeed;

    std::cout << "Enter desiredHeight: ";
    std::cin >> desiredHeight;

    std::cout << "Answer: " << lab1_var17(upSpeed, downSpeed, desiredHeight) << std::endl;

    return 0;
}
