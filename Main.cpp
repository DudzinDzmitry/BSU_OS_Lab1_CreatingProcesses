#include <windows.h>
#include <iostream>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::cout
            << "Данная программа генерирует текстовый файл отчета по заработной плате на основании списка сотрудников.\n";

    std::cout << "Введите имя бинарного файла для списка сотрудников (в виде \"имя_файла.bin\"):";
    std::string listName;
    std::cin >> listName;

    std::cout << "Введите количество записей в списке соответствующее количеству сотрудников:";
    std::string recordCount;
    std::cin >> recordCount;

    system("pause");
    return 0;
}