#include <iostream>
#include <memory_resource>
#include "src/memoryResource.h" // Подключаем вашу реализацию memory_resource
#include "src/stack.h"                   // Подключаем вашу реализацию контейнера Stack


namespace Containers {
// Простая пользовательская структура
struct CustomStruct {
    int id;
    std::string name;

    CustomStruct(int id, const std::string& name) : id(id), name(name) {}

    friend std::ostream& operator<<(std::ostream& os, const CustomStruct& obj) {
        os << "{ id: " << obj.id << ", name: \"" << obj.name << "\" }";
        return os;
    }
};

}

int main() {

    using namespace Containers;

    try {
        // Создаем фиксированный блок памяти
        constexpr std::size_t POOL_SIZE = 1024;
        MemoryResource memory_resource(POOL_SIZE);

        // Создаем стек с использованием PMR аллокатора
        std::pmr::polymorphic_allocator<double> alloc_double(&memory_resource);
        Stack<double, decltype(alloc_double)> stack_double(alloc_double);

        // Работа со стеком double
        stack_double.push(3.14);
        stack_double.push(1.618);
        stack_double.push(2.718);

        std::cout << "Stack of doubles:" << std::endl;
        while (!stack_double.empty()) {
            std::cout << stack_double.top() << std::endl;
            stack_double.pop();
        }

        // Создаем стек для пользовательского типа
        std::pmr::polymorphic_allocator<CustomStruct> alloc_custom(&memory_resource);
        Stack<CustomStruct, decltype(alloc_custom)> stack_custom(alloc_custom);

        // Работа со стеком CustomStruct
        stack_custom.push(CustomStruct(1, "Alice"));
        stack_custom.push(CustomStruct(2, "Bob"));
        stack_custom.push(CustomStruct(3, "Charlie"));

        std::cout << "\nStack of CustomStructs:" << std::endl;
        while (!stack_custom.empty()) {
            std::cout << stack_custom.top() << std::endl;
            stack_custom.pop();
        }

        std::cout << "\nMemory resource statistics:" << std::endl;
        std::cout << "Total size: " << memory_resource.get_total_size() << " bytes" << std::endl;
        std::cout << "Free blocks: " << memory_resource.get_free_blocks_count() << std::endl;
        std::cout << "Allocated blocks: " << memory_resource.get_allocated_blocks_count() << std::endl;


    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
