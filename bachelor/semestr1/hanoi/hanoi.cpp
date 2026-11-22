#include <iostream>
#include <clocale>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void hanoi(int n, char from, char to, char aux, int& moveNumber)
{
    if (n == 1)
    {
        ++moveNumber;
        cout << "Ход " << moveNumber << ": кольцо 1: "
             << from << " -> " << to << "\n";
        return;
    }

    hanoi(n - 1, from, aux, to, moveNumber);

    ++moveNumber;
    cout << "Ход " << moveNumber << ": кольцо " << n << ": "
         << from << " -> " << to << "\n";

    hanoi(n - 1, aux, to, from, moveNumber);
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    setlocale(LC_ALL, "Russian");

    const int DISKS = 5;
    cout << "Ханойская башня: " << DISKS << " колец, 3 стержня\n";
    cout << "Стержни: A - исходный, B - вспомогательный, C - целевой\n\n";

    int moves = 0;
    hanoi(DISKS, 'A', 'C', 'B', moves);

    cout << "\nВсего ходов: " << moves << "\n";
    cout << "Теоретический минимум: 2^" << DISKS << " - 1 = "
         << (1 << DISKS) - 1 << "\n";
    return 0;
}
