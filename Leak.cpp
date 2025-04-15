#include <iostream>

void memory_leak() {
    for (int i = 0; i < 100; ++i) {
        int* arr = new int[100]; // Утечка - нет соответствующего delete[]
        arr[0] = i; 
    }
    std::cout << "creat obj" << std::endl;
}

int main() {
    memory_leak();
}
