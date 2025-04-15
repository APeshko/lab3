# lab3

Для проверки утечек памяти:
      valgrind --leak-check=full ./lab3
      g++ -fsanitize=address -g manual_leak.cpp ./a.out

 std::unique_ptr и RAII
Реализован класс FileManager, который использует unique_ptr для автоматического управления файловым ресурсом. При выходе из области видимости файл гарантированно закрывается.

std::shared_ptr
Показано разделяемое владение ресурсом с помощью shared_ptr. Счетчик ссылок автоматически управляет временем жизни ресурса.

std::weak_ptr
Реализован паттерн "Наблюдатель" с использованием weak_ptr, который позволяет безопасно наблюдать за объектом без продления его времени жизни.
