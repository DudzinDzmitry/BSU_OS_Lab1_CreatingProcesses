#include <windows.h>
#include <fstream>

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    std::ofstream list(argv[0], std::ios::binary);

    list.close();
    return 0;
}