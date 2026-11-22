#include <iostream>
#include <clocale>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const int N = 7;

void fillMatrix(int a[N][N])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            // 0 - выше и главной, и побочной диагонали одновременно
            if (j > i && j < N - 1 - i)
                a[i][j] = 0;
            else
                a[i][j] = 1;
        }
    }
}

void printMatrix(const int a[N][N])
{
    cout << "    ";
    for (int j = 0; j < N; ++j)
        cout << j << " ";
    cout << "\n";

    for (int i = 0; i < N; ++i)
    {
        cout << "  " << i << " ";
        for (int j = 0; j < N; ++j)
            cout << a[i][j] << " ";
        cout << "\n";
    }
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    setlocale(LC_ALL, "Russian");

    cout << "Матрица " << N << "x" << N << ": нули выше главной и побочной диагоналей\n\n";
    cout << "Главная диагональ:  i = j\n";
    cout << "Побочная диагональ: i + j = " << N - 1 << "\n";
    cout << "Выше главной:       j > i\n";
    cout << "Выше побочной:      j < " << N - 1 << " - i\n";
    cout << "Условие нуля:       j > i && j < " << N - 1 << " - i\n\n";

    int a[N][N];
    fillMatrix(a);
    printMatrix(a);

    return 0;
}
