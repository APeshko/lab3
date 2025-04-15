#include <iostream>
#include <memory>
#include <fstream>


class File {
    std::unique_ptr<std::fstream> file; // умный указатель на файловый поток

public:
    explicit File (const std::string& filename) {
        //открытие файла через умный указатель
        file = std::make_unique<std::fstream>(filename, std::ios::out);
        
        // Проверка  открытия
        if (!file->is_open()) {
            throw std::runtime_error("Не удалось открыть файл");
        }
        std::cout << "Файл " << filename << " успешно открыт" << std::endl;
    }

    /**
     * Запись данных в файл
     */
    void write(const std::string& data) {
        // Проверяем, что файл доступен для записи
        if (file && *file) {
            *file << data << std::endl; // Безопасная запись
        } else {
            std::cout << "Ошибка записи: файл не доступен" << std::endl;
        }
    }

    // Деструктора нету unique_ptr автоматически закроет файл
};

int main() {
    try {
        // create менеджер файла (файл откроется автоматически)
        File manager("test.txt");
        
        // use файл через безопасный интерфейс
        manager.write("Первая запись");
        manager.write("Вторая запись");
        
    } catch (const std::exception& e) {
        // Обработка возможных ошибок
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
}
