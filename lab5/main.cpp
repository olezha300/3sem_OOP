#include <iostream>
#include <limits>

#include <StackMemoryResource.h>
#include <Stack.h>

struct Pair {
    int x;
    int y;
};

int main() {
    StackMemoryResource mr1;
    Stack<int> int_stack(&mr1);

    StackMemoryResource mr2;
    Stack<Pair> pair_stack(&mr2);

    std::cout << "Type 'help' to get info" << std::endl;

    while (true) {
        std::cout << "\nstack> ";
        std::string input;
        std::cin >> input;

        if (input == "exit") break;

        else if (input == "push") {
            std::string type;
            std::cin >> type;

            if (type == "int") {
                int elem;
                std::cin >> elem;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input!" << std::endl;
                    continue;
                }

                try {
                    int_stack.push(elem);
                } catch (const std::bad_alloc&) {
                    std::cout << "Stack is full!" << std::endl;
                }
            }

            else if (type == "pair") {
                Pair pair{};
                std::cin >> pair.x >> pair.y;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input!" << std::endl;
                    continue;
                }

                try {
                    pair_stack.push(pair);
                } catch (const std::bad_alloc&) {
                    std::cout << "Stack is full!" << std::endl;
                }
            }

            else {
                std::cout << "Invalid parameter 'type'!" << std::endl;
            }
        }

        else if (input == "print") {
            std::string type;
            std::cin >> type;

            if (type == "int") {
                if (int_stack.empty()) {
                    std::cout << "Stack is empty!" << std::endl;
                } else {
                    std::cout << int_stack << std::endl;
                }
            }

            else if (type == "pair") {
                if (pair_stack.empty()) {
                    std::cout << "Stack is empty!" << std::endl;
                } else {
                    std::cout << '[';
                    for (const auto& [x, y] : pair_stack)
                        std::cout << " (" << x << ", " << y << ')';
                    std::cout << " ]" << std::endl;
                }
            }

            else {
                std::cout << "Invalid parameter 'type'!" << std::endl;
            }
        }

        else if (input == "pop") {
            std::string type;
            std::cin >> type;

            if (type == "int") {
                if (int_stack.empty()) {
                    std::cout << "Stack is empty!" << std::endl;
                } else {
                    std::cout << *int_stack.pop() << std::endl;
                }
            }

            else if (type == "pair") {
                if (pair_stack.empty()) {
                    std::cout << "Stack is empty!" << std::endl;
                } else {
                    const auto pair = pair_stack.pop();
                    std::cout << " (" << pair->x << ", " << pair->y << ')' << std::endl;
                }
            }

            else {
                std::cout << "Invalid parameter 'type'!" << std::endl;
            }
        }

        else if (input == "clear") {
            std::string type;
            std::cin >> type;

            if (type == "int") {
                int_stack.clear();
                std::cout << "Integer stack cleared!" << std::endl;
            }

            else if (type == "pair") {
                pair_stack.clear();
                std::cout << "Pair stack cleared!" << std::endl;
            }

            else {
                std::cout << "Invalid parameter 'type'!" << std::endl;
            }
        }

        else if (input == "size") {
            std::string type;
            std::cin >> type;

            if (type == "int") {
                std::cout << "Size of integer stack: " << int_stack.size() << std::endl;
            }

            else if (type == "pair") {
                std::cout << "Size of pair stack: " << pair_stack.size() << std::endl;
            }

            else {
                std::cout << "Invalid parameter 'type'!" << std::endl;
            }
        }

        else if (input == "help") {
            std::cout << "Commands:\n";
            std::cout << " push int <number> : Add number to integer stack\n";
            std::cout << " push pair <x> <y> : Add pair of numbers to pair stack\n";
            std::cout << " print int/pair : Print contents of the stack\n";
            std::cout << " pop int/pair : Remove and display top element of the stack\n";
            std::cout << " clear int/pair : Clear the stack\n";
            std::cout << " size int/pair : Show size of the stack\n";
            std::cout << " exit : Exit the program\n";
        }

        else {
            std::cout << "Command not found!" << std::endl;
        }
    }
    return 0;
}
