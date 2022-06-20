#include <fstream>

int main(int argc, char *argv[]) {
    std::ofstream report(argv[1]);

    report << "Отчет по файлу \"" << argv[0] << "\"\n";
    report << "Номер сотрудника, имя сотрудника, отработанные часы, заработная плата\n";

    std::ifstream list(argv[0], std::ios::binary);

    list.close();
    report.close();

    return 0;
}