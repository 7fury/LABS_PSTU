#include <iostream>
#include <cctype>
#include <clocale>

using namespace std;

// Перегруженная функция 1:
// количество нечётных элементов массива целых чисел
int count(int n, const int a[])
{
    int result = 0;

    for (int i = 0; i < n; ++i)
        if (a[i] % 2 != 0)
            ++result;

    return result;
}

// Перегруженная функция 2:
// количество слов в строке
int count(const char* s)
{
    int result = 0;
    bool inWord = false;

    for (int i = 0; s[i] != '\0'; ++i)
    {
        if (isspace(static_cast<unsigned char>(s[i])))
        {
            inWord = false;
        }
        else if (!inWord)
        {
            inWord = true;
            ++result;
        }
    }

    return result;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int a[] = { 12, -7, 0, 15, 8, -3, 21, 4, 9, -11, 6 };
    int n = sizeof(a) / sizeof(a[0]);

    cout << "Массив: ";
    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << "\n";

    cout << "Количество нечётных элементов: " << count(n, a) << "\n";

    const char* s =
        "Overloading functions in C++ makes the program more expressive";

    cout << "\nСтрока: " << s << "\n";
    cout << "Количество слов в строке: " << count(s) << "\n";

    return 0;
}
