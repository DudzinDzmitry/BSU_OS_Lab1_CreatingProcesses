#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
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
    int recordCount;
    std::cin >> recordCount;

    std::ostringstream tempStrStream;
    tempStrStream << recordCount;

    std::string cmdLine = listName + " " + tempStrStream.str();
    if (!startProcess("creator.exe", cmdLine.c_str())) {
        std::cout << "Не удалось запустить процесс creator.exe, поскольку при создании была встречена ошибка " << GetLastError() << "\n";
        system("pause");
        return 1;
    }

    employee temp = {};

    std::ifstream list(listName.c_str(), std::ios::binary);

    while (list.read((char *) &temp, sizeof(employee))) {
        std::cout << temp.ID << " " << temp.fullName << " " << temp.hoursWorked << ";\n";
    }

    std::cout << "Введите имя текстового файла для отчета по заработной плате (в виде \"имя_файла.txt\"):";
    std::string reportName;
    std::cin >> reportName;

    std::cout << "Введите плату за час:";
    double payPerHour;

    std::cin >> payPerHour;
    tempStrStream.str("");
    tempStrStream << payPerHour;

    cmdLine = listName + " " + reportName + " " + tempStrStream.str();
    if (!startProcess("reporter.exe", cmdLine.c_str())) {
        std::cout << "Не удалось запустить процесс reporter.exe, поскольку при создании была встречена ошибка " << GetLastError() << "\n";
        system("pause");
        return 1;
    }

    std::string record;
    std::ifstream report(reportName.c_str());

    while (getline(report, record)) std::cout << record << ";\n";

    system("pause");
    return 0;
}