#include <windows.h>
#include <iostream>
#include <fstream>
#include "Employee.h"

bool startProcess(const char *appName, const char *cmdLine) {
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    PROCESS_INFORMATION pi;

    if (!CreateProcess(appName, const_cast<char *>(cmdLine), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si,
                       &pi))
        return false;

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return true;
}

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

    std::string cmdLine = listName + " " + recordCount;
    if (!startProcess("creator.exe", cmdLine.c_str())) return GetLastError();

    employee temp = {};

    std::ifstream list(listName.c_str(), std::ios::binary);

    while (list.read((char *) &temp, sizeof(employee))) {
        std::cout << temp.ID << " " << temp.fullName << " " << temp.hoursWorked << ";\n";
    }

    std::cout << "Введите имя текстового файла для отчета по заработной плате (в виде \"имя_файла.txt\"):";
    std::string reportName;
    std::cin >> reportName;

    std::cout << "Введите плату за час:";
    std::string payPerHour;
    std::cin >> payPerHour;

    cmdLine = listName + " " + reportName + " " + payPerHour;
    if (!startProcess("reporter.exe", cmdLine.c_str())) return GetLastError();

    std::string record;
    std::ifstream report(reportName.c_str());

    while (getline(report, record)) std::cout << record << ";\n";

    system("pause");
    return 0;
}