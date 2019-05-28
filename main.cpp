#include <iostream>
#include <string>


int main() {
    int ten = 10;

    ten++;
    ten+=2;

    std::cout << "Hello World\n";
    std::cout << "Input: ";
    std::string data;
    getline(std::cin, data);
    std::cout << "Output: " << data << "\n\n";
    return 0;
}