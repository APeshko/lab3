#include <iostream>
#include <memory>

class Resource {
public:
    Resource() {
        std::cout << "Resource";
    }
    ~Resource() {
        std::cout << "Resource svob";
    }
};

class Class {
    std::unique_ptr<Resource> resource;
public:
    Class() : resource(std::make_unique<Resource>()) { }
};

int main() {
    Class obj; // Resource освобождён при вых из ОВ
    return 0;
}
