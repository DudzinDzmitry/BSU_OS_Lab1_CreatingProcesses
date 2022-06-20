#include <windows.h>
#include <fstream>
#include <iostream>
#include "Employee.h"

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    std::ofstream list(argv[0], std::ios::binary);

    int i = 0;
    long recordCount = strtol(argv[1], NULL, 10);
    while (i < recordCount) {
        employee temp = {};
        std::cout << "Введите запись (в виде номер сотрудника, имя сотрудника, отработанные часы):\n";
        std::cin >> temp.ID >> temp.fullName >> temp.hoursWorked;
        list.write((char *) &temp, sizeof(employee));
        ++i;
    }

    list.close();
    return 0;
}