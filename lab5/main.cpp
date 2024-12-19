#include <iostream>
#include <stack>
#include <memory_resource>
#include <CustomMemoryResource.hpp>
#include <CustomStack.hpp>

int main() {
    CustomMemoryResource custom_resource;

    CustomStack<int> cs(&custom_resource);
    std::cout << cs.get_size() << std::endl;
    std::cout << cs.get_capacity() << std::endl;

    std::cout << std::endl;

    cs.push_back(1);
    std::cout << cs.top() << std::endl;
    cs.push_back(2);
    std::cout << cs.top() << std::endl;


    std::cout << cs.get_size() << std::endl;
    std::cout << cs.get_capacity() << std::endl;

    cs.pop_back();

    std::cout << "-----------\n";

    std::cout << cs.get_size() << std::endl;
    std::cout << cs.get_capacity() << std::endl;
    std::cout << cs.top() << std::endl;

    std::cout << std::endl;


}
