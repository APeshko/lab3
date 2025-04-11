#include <iostream>
#include <memory>

class Observer {
public:
    void observe(std::shared_ptr<int> sharedPtr) {
        weakPtr = sharedPtr; // Наблюдение без продления жизни
    }

    void check() {
        if (auto lockedPtr = weakPtr.lock()) { // Пытаемся получить доступ
            std::cout << "Resource is alive: " << *lockedPtr << "\n";
        } else {
            std::cout << "Resource is no longer available\n";
        }
    }

private:
    std::weak_ptr<int> weakPtr; // weak_ptr не увеличивает счетчик ссылок
};

int main() {
    std::shared_ptr<int> resource = std::make_shared<int>(42);
    Observer observer;

    observer.observe(resource);
    observer.check(); // Должно показать, что ресурс доступен

    resource.reset(); // Унич ресурс
    observer.check(); // Должно показать, что ресурс больше не доступен

    return 0;
}
