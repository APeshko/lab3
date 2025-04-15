#include <iostream>
#include <memory> // для умных указателей (unique_ptr)
#include <fstream> // для управление файлами

class Class { //управление файловым ресурсом
    std::unique_ptr<std::fstream> file; // Умный указатель на файловый поток
public:
    explicit Class(const std::string& filename) { //через explicit не даст неявное преобразование 
        file = std::make_unique<std::fstream>(filename, std::ios::out); //файл открывается для записи, std::make_unique создает unique_ptr с новым fstream
        //не забыть, что std::ios::out - режим открытия файла (запись)
        if (!file->is_open()) { //проверяю открылся ли он
            throw std::runtime_error("Failed to open file"); //при таком раскладе выбрасывается исключение об ошибке
        }
        std::cout << "File opened: " << filename << std::endl;
    }

    ~Class() {
        if (file && file->is_open()) { // Проверка, что указатель не nullptr и файл открыт
            file->close(); // Закрытие файла
            std::cout << "File closed" << std::endl;
        }
    }

    void write(const std::string& data) {
        if (file) { // Проверка, что указатель не nullptr
            *file << data << std::endl;
        }
    }

    Class(const FileResource&) = delete;  // Запрет копирования
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


