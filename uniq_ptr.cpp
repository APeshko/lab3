#include <iostream>
#include <memory>
#include <fstream>

class FileResource {
    std::unique_ptr<std::fstream> file;
public:
    explicit FileResource(const std::string& filename) {
        file = std::make_unique<std::fstream>(filename, std::ios::out);
        if (!file->is_open()) {
            throw std::runtime_error("Failed to open file");
        }
        std::cout << "File opened: " << filename << std::endl;
    }

    ~FileResource() {
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
    FileResource(const FileResource&) = delete;
    FileResource& operator=(const FileResource&) = delete;

    // Разрешаем перемещение
    FileResource(FileResource&&) = default;
    FileResource& operator=(FileResource&&) = default;
};

int main() {
    try {
        FileResource file("test.txt");
        file.write("Hello RAII!");
        
        // Демонстрация перемещения
        FileResource movedFile = std::move(file);
        movedFile.write("Moved resource works!");
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}


