#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <clocale>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const int NAME_LEN = 64;
const char* FILE_NAME = "owners.dat";
const char* TEMP_NAME = "owners.tmp";

struct CarOwner
{
    char fullName[NAME_LEN];
    char carNumber[16];
    char techPassport[20];
    char gaiDept[NAME_LEN];
};

void printOwner(const CarOwner& o, int number)
{
    cout << number << ". " << o.fullName << "\n"
         << "   Номер автомобиля: " << o.carNumber << "\n"
         << "   Номер техпаспорта: " << o.techPassport << "\n"
         << "   Отделение ГАИ: " << o.gaiDept << "\n";
}

int printFile(const char* fileName)
{
    FILE* f = fopen(fileName, "rb");
    if (f == NULL)
    {
        cout << "Ошибка: не удалось открыть файл " << fileName << "\n";
        return -1;
    }

    CarOwner o;
    int count = 0;
    cout << "\nСодержимое файла " << fileName << ":\n";
    while (fread(&o, sizeof(CarOwner), 1, f) == 1)
    {
        ++count;
        printOwner(o, count);
    }

    if (ferror(f))
    {
        cout << "Ошибка чтения файла.\n";
        fclose(f);
        return -1;
    }

    fclose(f);
    if (count == 0)
        cout << "Файл пуст.\n";
    return count;
}

bool createFile(const char* fileName, const CarOwner* owners, int n)
{
    FILE* f = fopen(fileName, "wb");
    if (f == NULL)
    {
        cout << "Ошибка: не удалось создать файл " << fileName << "\n";
        return false;
    }

    size_t written = fwrite(owners, sizeof(CarOwner), n, f);
    if (written != (size_t)n)
    {
        cout << "Ошибка записи файла.\n";
        fclose(f);
        return false;
    }

    fclose(f);
    return true;
}

bool sameSurname(const char* fullName, const char* surname)
{
    size_t len = strlen(surname);
    if (strncmp(fullName, surname, len) != 0)
        return false;
    return fullName[len] == ' ' || fullName[len] == '\0';
}

bool deleteByCarNumber(const char* fileName, const char* carNumber)
{
    FILE* in = fopen(fileName, "rb");
    if (in == NULL)
    {
        cout << "Ошибка: не удалось открыть файл " << fileName << "\n";
        return false;
    }

    FILE* out = fopen(TEMP_NAME, "wb");
    if (out == NULL)
    {
        cout << "Ошибка: не удалось создать временный файл.\n";
        fclose(in);
        return false;
    }

    CarOwner o;
    bool found = false;
    while (fread(&o, sizeof(CarOwner), 1, in) == 1)
    {
        if (!found && strcmp(o.carNumber, carNumber) == 0)
        {
            found = true;
            cout << "\nУдалена запись: " << o.fullName
                 << ", автомобиль " << o.carNumber << "\n";
            continue;
        }
        fwrite(&o, sizeof(CarOwner), 1, out);
    }

    fclose(in);
    fclose(out);
    remove(fileName);
    rename(TEMP_NAME, fileName);

    if (!found)
    {
        cout << "\nЗапись с номером " << carNumber << " не найдена.\n";
        return false;
    }
    return true;
}

bool insertBeforeSurname(const char* fileName, const char* surname,
                         const CarOwner* add, int addCount)
{
    FILE* in = fopen(fileName, "rb");
    if (in == NULL)
    {
        cout << "Ошибка: не удалось открыть файл " << fileName << "\n";
        return false;
    }

    FILE* out = fopen(TEMP_NAME, "wb");
    if (out == NULL)
    {
        cout << "Ошибка: не удалось создать временный файл.\n";
        fclose(in);
        return false;
    }

    CarOwner o;
    bool inserted = false;
    while (fread(&o, sizeof(CarOwner), 1, in) == 1)
    {
        if (!inserted && sameSurname(o.fullName, surname))
        {
            fwrite(add, sizeof(CarOwner), addCount, out);
            inserted = true;
        }
        fwrite(&o, sizeof(CarOwner), 1, out);
    }

    fclose(in);
    fclose(out);

    if (!inserted)
    {
        remove(TEMP_NAME);
        cout << "\nЗапись с фамилией " << surname << " не найдена.\n";
        return false;
    }

    remove(fileName);
    rename(TEMP_NAME, fileName);
    cout << "\nПеред записью с фамилией " << surname
         << " добавлено записей: " << addCount << "\n";
    return true;
}

void inputOwner(CarOwner& o)
{
    cout << "Фамилия, имя, отчество: ";
    cin.getline(o.fullName, NAME_LEN);
    cout << "Номер автомобиля: ";
    cin.getline(o.carNumber, sizeof(o.carNumber));
    cout << "Номер техпаспорта: ";
    cin.getline(o.techPassport, sizeof(o.techPassport));
    cout << "Отделение регистрации ГАИ: ";
    cin.getline(o.gaiDept, NAME_LEN);
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    setlocale(LC_ALL, "Russian");

    cout << "Лабораторная работа № 8. Блоковый ввод-вывод\n";
    cout << "Вариант 22. Структура \"Владелец автомобиля\"\n\n";
    cout << "1 - демонстрационный набор данных\n";
    cout << "2 - ввод данных с клавиатуры\n";
    cout << "Выберите режим: ";

    int mode = 1;
    cin >> mode;
    cin.ignore();

    CarOwner owners[16];
    int n = 0;

    if (mode == 1)
    {
        CarOwner demo[] = {
            {"Иванов Иван Иванович", "A123BC", "7701 123456", "ГИБДД Перми"},
            {"Петров Пётр Петрович", "B456DE", "7702 234567", "ГИБДД Пермского края"},
            {"Сидоров Сидор Сидорович", "C789FG", "7703 345678", "ГИБДД Березников"},
            {"Смирнова Анна Сергеевна", "E321HJ", "7704 456789", "ГИБДД Соликамска"},
            {"Кузнецов Олег Викторович", "K654LM", "7705 567890", "ГИБДД Кунгура"}
        };
        n = sizeof(demo) / sizeof(demo[0]);
        for (int i = 0; i < n; ++i)
            owners[i] = demo[i];
        cout << "\nВыбран демонстрационный набор из " << n << " записей.\n";
    }
    else
    {
        cout << "Введите количество записей (не менее 5): ";
        cin >> n;
        cin.ignore();
        if (n < 5 || n > 16)
        {
            cout << "Недопустимое количество записей.\n";
            return 1;
        }
        for (int i = 0; i < n; ++i)
        {
            cout << "\nЗапись " << i + 1 << ":\n";
            inputOwner(owners[i]);
        }
    }

    if (!createFile(FILE_NAME, owners, n))
        return 1;
    cout << "\nДвоичный файл " << FILE_NAME << " сформирован. Записей: " << n << "\n";
    printFile(FILE_NAME);

    char carNumber[16];
    if (mode == 1)
        strcpy(carNumber, "B456DE");
    else
    {
        cout << "\nВведите номер автомобиля для удаления: ";
        cin.getline(carNumber, sizeof(carNumber));
    }
    deleteByCarNumber(FILE_NAME, carNumber);

    char surname[NAME_LEN];
    if (mode == 1)
        strcpy(surname, "Смирнова");
    else
    {
        cout << "Введите фамилию, перед которой добавить 2 записи: ";
        cin.getline(surname, NAME_LEN);
    }

    CarOwner add[2];
    if (mode == 1)
    {
        CarOwner demoAdd[] = {
            {"Новиков Павел Андреевич", "H111AA", "7706 678901", "ГИБДД Перми"},
            {"Орлова Мария Игоревна", "M222BB", "7707 789012", "ГИБДД Краснокамска"}
        };
        add[0] = demoAdd[0];
        add[1] = demoAdd[1];
        cout << "\nДобавляются две демонстрационные записи.\n";
    }
    else
    {
        for (int i = 0; i < 2; ++i)
        {
            cout << "\nНовая запись " << i + 1 << ":\n";
            inputOwner(add[i]);
        }
    }

    insertBeforeSurname(FILE_NAME, surname, add, 2);
    printFile(FILE_NAME);

    return 0;
}
