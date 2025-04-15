#include <iostream>
#include <memory>
#include <vector>
//про раздельное владение и доступ к одним данным 
class Class {
public:
    Class() { std::cout << "Ресурс создан"; }
    ~Class() { std::cout << "Ресурс уничтожен"; }
};

int main() {
    auto resource = std::make_shared<Class>();
    
    std::vector<std::shared_ptr<Class>> owners;
    
    for (int i = 0; i < 3; ++i) {
        owners.push_back(resource);
        std::cout << "Количество ссылок: " << resource.use_count() << std::endl;
    }
    
    owners.clear();
    std::cout << "Количество ссылок после очистки: " << resource.use_count() << std::endl;
    
    return 0;
}
