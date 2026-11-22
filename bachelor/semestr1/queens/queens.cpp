#include <iostream>
#include <cstdlib>
#include <clocale>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const int N = 8;

bool isSafe(int row, int col, const int queens[])
{
    for (int r = 0; r < row; ++r)
    {
        if (queens[r] == col)
            return false;
        if (abs(queens[r] - col) == abs(r - row))
            return false;
    }
    return true;
}

void printBoard(const int queens[])
{
    cout << "\n    a b c d e f g h\n";
    for (int row = 0; row < N; ++row)
    {
        cout << "  " << N - row << " ";
        for (int col = 0; col < N; ++col)
            cout << (queens[row] == col ? "Q " : ". ");
        cout << "\n";
    }
    cout << "\n";
}

void solve(int row, int queens[], int& solutions, long long& nodes,
           bool& firstPrinted)
{
    ++nodes;

    if (row == N)
    {
        ++solutions;
        if (!firstPrinted)
        {
            cout << "Первое найденное решение:\n";
            printBoard(queens);
            firstPrinted = true;
        }
        return;
    }

    for (int col = 0; col < N; ++col)
    {
        if (isSafe(row, col, queens))
        {
            queens[row] = col;
            solve(row + 1, queens, solutions, nodes, firstPrinted);
        }
    }
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    setlocale(LC_ALL, "Russian");

    cout << "Задача о восьми ферзях\n";
    cout << "Расстановка 8 ферзей на доске 8x8 без взаимных атак\n\n";

    int queens[N] = {0};
    int solutions = 0;
    long long nodes = 0;
    bool firstPrinted = false;

    solve(0, queens, solutions, nodes, firstPrinted);

    cout << "Всего решений: " << solutions << "\n";
    cout << "Просмотрено узлов дерева поиска: " << nodes << "\n";
    return 0;
}
