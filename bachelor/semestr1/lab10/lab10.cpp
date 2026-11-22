#include <iostream>
#include <cstring>
#include <clocale>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const int MAX_LEN = 128;

char* copyString(const char* s)
{
    int len = strlen(s);
    char* result = new char[len + 1];
    strcpy(result, s);
    return result;
}

char** createArray(int n)
{
    char** a = new char*[n];
    for (int i = 0; i < n; ++i)
        a[i] = NULL;
    return a;
}

void freeArray(char** a, int n)
{
    if (a == NULL)
        return;
    for (int i = 0; i < n; ++i)
        delete[] a[i];
    delete[] a;
}

void printArray(char** a, int n, const char* title)
{
    cout << "\n" << title << " (" << n << " строк):\n";
    for (int i = 0; i < n; ++i)
        cout << "  " << i + 1 << ". " << a[i] << "\n";
}

char** removeK(char** a, int n, int start, int k, int& newN)
{
    // start - номер первой удаляемой строки (от 1), k - сколько удалить
    for (int i = start - 1; i < start - 1 + k; ++i)
        delete[] a[i];

    newN = n - k;
    char** result = new char*[newN];
    int j = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i < start - 1 || i >= start - 1 + k)
            result[j++] = a[i];
    }
    delete[] a;
    return result;
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    setlocale(LC_ALL, "Russian");

    cout << "Лабораторная работа № 10. Динамические массивы\n";
    cout << "Вариант 22: удалить К строк, начиная со строки с заданным номером\n\n";
    cout << "1 - демонстрационный набор строк\n";
    cout << "2 - ввод строк с клавиатуры\n";
    cout << "Выберите режим: ";

    int mode = 1;
    cin >> mode;
    cin.ignore();

    int n = 0;
    char** a = NULL;

    if (mode == 1)
    {
        const char* demo[] = {
            "Москва",
            "Санкт-Петербург",
            "Пермь",
            "Екатеринбург",
            "Новосибирск",
            "Казань",
            "Самара",
            "Омск"
        };
        n = sizeof(demo) / sizeof(demo[0]);
        a = createArray(n);
        for (int i = 0; i < n; ++i)
            a[i] = copyString(demo[i]);
        cout << "\nВыбран демонстрационный набор из " << n << " строк.\n";
    }
    else
    {
        cout << "Введите количество строк: ";
        cin >> n;
        cin.ignore();
        if (n <= 0 || n > 32)
        {
            cout << "Недопустимое количество строк.\n";
            return 1;
        }
        a = createArray(n);
        char buffer[MAX_LEN];
        for (int i = 0; i < n; ++i)
        {
            cout << "Строка " << i + 1 << ": ";
            cin.getline(buffer, MAX_LEN);
            a[i] = copyString(buffer);
        }
    }

    printArray(a, n, "Исходный массив");

    int start = 3;
    int k = 3;
    if (mode == 1)
    {
        cout << "\nУдаляются 3 строки, начиная со строки 3.\n";
    }
    else
    {
        cout << "\nВведите номер первой удаляемой строки: ";
        cin >> start;
        cout << "Введите количество удаляемых строк: ";
        cin >> k;
    }

    if (start < 1 || start > n || k < 1 || k > n - start + 1)
    {
        cout << "Ошибка: недопустимые номер строки или количество.\n";
        freeArray(a, n);
        return 1;
    }

    int newN = 0;
    a = removeK(a, n, start, k, newN);
    n = newN;

    printArray(a, n, "Массив после удаления");
    freeArray(a, n);
    cout << "\nДинамическая память освобождена.\n";
    return 0;
}
