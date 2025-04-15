#include <iostream>
#include <fstream>

class Class {
    std::fstream* file; // указатель на файловый поток
public:
    explicit Class(const std::string& filename) {
        file = new std::fstream(filename, std::ios::out); // Выделение памяти вручную
        if (!file->is_open()) {
            // Утечка: память не освобождается при исключении
            throw std::runtime_error("Failed to open file");
        }
        std::cout << "File opened: " << filename << std::endl;
    }

    ~Class() {
        if (file && file->is_open()) {
            file->close(); // Закрытие файла, но без удаления объекта
        }
        std::cout << "~Class(): Memory leaked for file handler!" << std::endl;
    }

    void write(const std::string& data) {
        if (file) {
            *file << data << std::endl;
        }
    }

    // Запрещаем копирование и перемещение (для усугубления утечек)
    Class(const Class&) = delete;
    Class& operator=(const Class&) = delete;
    Class(Class&&) = delete;
    Class& operator=(Class&&) = delete;
};

void create_leaks() {
    for (int i = 0; i < 5; ++i) {
        Class obj("leak_file_" + std::to_string(i) + ".txt");
        obj.write("This will leak memory!");
    } // Утечка 5 файловых дескрипторов и памяти
}

int main() {
    try {
        create_leaks();
        std::cout << "Program finished (with memory leaks!)" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
