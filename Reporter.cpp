#include <fstream>
#include <cstdlib>
#include "Employee.h"

int main(int argc, char *argv[]) {
    std::ofstream report(argv[1]);

    report << "Отчет по файлу \"" << argv[0] << "\"\n";
    report << "Номер сотрудника, имя сотрудника, отработанные часы, заработная плата\n";

    std::ifstream list(argv[0], std::ios::binary);

    employee temp = {};
    double payPerHour = strtod(argv[2], NULL);

    while (list.read((char *) &temp, sizeof(employee)))
        report << temp.ID << " " << temp.fullName << " " << temp.hoursWorked << " " << temp.hoursWorked * payPerHour
               << "\n";

    list.close();
    report.close();

    return 0;
}