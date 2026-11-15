#include <iostream>
#include <iomanip>
#include <clocale>

using namespace std;

const int N = 5;
const int M = 6;

// Среднее арифметическое элементов столбца col
double columnAverage(const int a[][M], int n, int col)
{
    int sum = 0;
    for (int i = 0; i < n; ++i)
        sum += a[i][col];

    return static_cast<double>(sum) / n;
}

// Количество элементов столбца col, превышающих значение value
int countGreater(const int a[][M], int n, int col, double value)
{
    int count = 0;
    for (int i = 0; i < n; ++i)
        if (a[i][col] > value)
            ++count;

    return count;
}

// Печать двумерного массива
void printMatrix(const int a[][M], int n, int m)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            cout << setw(5) << a[i][j];
        cout << '\n';
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int a[N][M] = {
        { 4, 7, 2, 9, 5, 3 },
        { 8, 1, 6, 4, 7, 8 },
        { 6, 5, 9, 2, 1, 4 },
        { 2, 8, 4, 7, 6, 9 },
        { 9, 3, 5, 6, 8, 2 }
    };

    cout << "Исходная матрица " << N << " x " << M << ":\n";
    printMatrix(a, N, M);

    cout << fixed << setprecision(3);

    double avg = columnAverage(a, N, 0);
    cout << "\nСреднее арифметическое первого столбца: " << avg << "\n\n";

    for (int j = 1; j < M; ++j)
    {
        int count = countGreater(a, N, j, avg);

        cout << "Столбец " << j + 1
             << ": элементов больше среднего предыдущего столбца ("
             << avg << "): " << count << "\n";

        avg = columnAverage(a, N, j);
    }

    return 0;
}
