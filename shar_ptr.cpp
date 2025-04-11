#include <iostream>
#include <memory>

void sharedPtrDemo() {
    std::shared_ptr<int> p1 = std::make_shared<int>(10);
    {
        std::shared_ptr<int> p2 = p1; // p2 разделяет владение
        std::cout << "Value: " << *p2 << ", Count: " << p1.use_count() << "\n"; // Count: 2
    }
    std::cout << "Count after p2 goes out of scope: " << p1.use_count() << "\n"; // Count: 1
}

int main() {
    sharedPtrDemo();
    return 0; // Ресурс автоматически освобождается, когда последний shared_ptr уничтожается.
}
