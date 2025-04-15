#include <iostream>
#include <memory>
#include <fstream>

class Class {
    std::unique_ptr<std::fstream> file;
public:
    explicit Class(const std::string& filename) {
        file = std::make_unique<std::fstream>(filename, std::ios::out);
        if (!file->is_open()) {
            throw std::runtime_error("Failed to open file");
        }
        std::cout << "File opened: " << filename << std::endl;
    }

    ~Class() {
        if (file && file->is_open()) {
            file->close();
            std::cout << "File closed" << std::endl;
        }
    }

    void write(const std::string& data) {
        if (file) {
            *file << data << std::endl;
        }
    }

    // Запрещаем копирование
    Class(const FileResource&) = delete;
    Class& operator=(const Class&) = delete;

    // Разрешаем перемещение
    Class(Class&&) = default;
    Class& operator=(Class&&) = default;
};

int main() {
    try {
        Class file("test.txt");
        file.write("ок!");
        
        // Демонстрация перемещения
        Class movedFile = std::move(file);
        movedFile.write("Moved resource works!");
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}


