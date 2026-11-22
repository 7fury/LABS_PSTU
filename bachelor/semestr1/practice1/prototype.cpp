#include <iostream>
#include <clocale>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Прототип функции объявлен до её использования
void sum(int, int);

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    setlocale(LC_ALL, "Russian");

    int a, b;
    cout << "Введите первое число: ";
    cin >> a;
    cout << "Введите второе число: ";
    cin >> b;
    sum(a, b);
    return 0;
}

void sum(int a, int b)
{
    cout << "Результат суммы: " << a + b << endl;
}
