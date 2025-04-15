# lab3

Для проверки утечек памяти:
      valgrind --leak-check=full ./lab3
      g++ -fsanitize=address -g manual_leak.cpp ./a.out
