#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <clocale>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const char* F1_NAME = "F1.txt";
const char* F2_NAME = "F2.txt";
const int LINE_LEN = 512;

int utf8Length(unsigned char c)
{
    if (c < 0x80) return 1;
    if ((c >> 5) == 0x6) return 2;
    if ((c >> 4) == 0xE) return 3;
    return 4;
}

unsigned int utf8Code(const char* s, int len)
{
    unsigned char c = (unsigned char)s[0];
    if (len == 1) return c;
    if (len == 2)
        return ((c & 0x1F) << 6) | ((unsigned char)s[1] & 0x3F);
    if (len == 3)
        return ((c & 0x0F) << 12) |
               (((unsigned char)s[1] & 0x3F) << 6) |
               ((unsigned char)s[2] & 0x3F);
    return 0;
}

bool isRussianVowel(unsigned int code)
{
    switch (code)
    {
        case 0x430: case 0x435: case 0x451: case 0x438:
        case 0x43E: case 0x443: case 0x44B: case 0x44D:
        case 0x44E: case 0x44F:
        case 0x410: case 0x415: case 0x401: case 0x418:
        case 0x41E: case 0x423: case 0x42B: case 0x42D:
        case 0x42E: case 0x42F:
            return true;
        default:
            return false;
    }
}

int countVowels(const char* word)
{
    int count = 0;
    int i = 0;
    while (word[i] != '\0')
    {
        int len = utf8Length((unsigned char)word[i]);
        if (isRussianVowel(utf8Code(word + i, len)))
            ++count;
        i += len;
    }
    return count;
}

bool isAsciiSpace(unsigned char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n' ||
           c == '\f' || c == '\v';
}

int countWords(const char* line)
{
    int count = 0;
    bool inWord = false;
    for (int i = 0; line[i] != '\0'; ++i)
    {
        if (isAsciiSpace((unsigned char)line[i]))
            inWord = false;
        else if (!inWord)
        {
            inWord = true;
            ++count;
        }
    }
    return count;
}

void createF1()
{
    const char* lines[] = {
        "Утро выдалось тихим и ясным.",
        "Птицы поют.",
        "Программирование развивает логическое мышление.",
        "Рыбак сидит.",
        "Над рекой поднимался лёгкий туман.",
        "Тишина.",
        "Дети бегут к воде.",
        "Солнце светит.",
        "Летний день радует нас теплом.",
        "Ветер стих.",
        "На берегу горит костёр.",
        "Вечер обещает быть спокойным."
    };
    int n = sizeof(lines) / sizeof(lines[0]);

    FILE* f = fopen(F1_NAME, "w");
    if (f == NULL)
    {
        cout << "Ошибка: не удалось создать файл " << F1_NAME << "\n";
        return;
    }

    for (int i = 0; i < n; ++i)
        fprintf(f, "%s\n", lines[i]);
    fclose(f);
    cout << "Файл " << F1_NAME << " создан. Строк: " << n << "\n";
}

void printFile(const char* fileName)
{
    FILE* f = fopen(fileName, "r");
    if (f == NULL)
    {
        cout << "Ошибка: не удалось открыть файл " << fileName << "\n";
        return;
    }

    cout << "\nСодержимое файла " << fileName << ":\n";
    char line[LINE_LEN];
    int number = 0;
    while (fgets(line, LINE_LEN, f) != NULL)
    {
        ++number;
        int len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
            line[--len] = '\0';
        cout << number << ". " << line << "\n";
    }

    if (ferror(f))
        cout << "Ошибка чтения файла.\n";
    fclose(f);
}

int copyLongLines()
{
    FILE* in = fopen(F1_NAME, "r");
    if (in == NULL)
    {
        cout << "Ошибка: не удалось открыть файл " << F1_NAME << "\n";
        return -1;
    }

    FILE* out = fopen(F2_NAME, "w");
    if (out == NULL)
    {
        cout << "Ошибка: не удалось создать файл " << F2_NAME << "\n";
        fclose(in);
        return -1;
    }

    char line[LINE_LEN];
    int copied = 0;
    while (fgets(line, LINE_LEN, in) != NULL)
    {
        if (countWords(line) > 2)
        {
            fputs(line, out);
            ++copied;
        }
    }

    fclose(in);
    fclose(out);
    return copied;
}

void findWordWithMostVowels()
{
    FILE* f = fopen(F2_NAME, "r");
    if (f == NULL)
    {
        cout << "Ошибка: не удалось открыть файл " << F2_NAME << "\n";
        return;
    }

    char line[LINE_LEN];
    int wordNumber = 0;
    int bestNumber = 0;
    int bestVowels = -1;
    char bestWord[LINE_LEN] = "";

    while (fgets(line, LINE_LEN, f) != NULL)
    {
        int i = 0;
        while (line[i] != '\0')
        {
            while (line[i] != '\0' && isAsciiSpace((unsigned char)line[i]))
                ++i;
            if (line[i] == '\0')
                break;

            int start = i;
            while (line[i] != '\0' && !isAsciiSpace((unsigned char)line[i]))
                ++i;
            int len = i - start;

            ++wordNumber;
            char word[LINE_LEN];
            if (len >= LINE_LEN) len = LINE_LEN - 1;
            strncpy(word, line + start, len);
            word[len] = '\0';

            int vowels = countVowels(word);
            if (vowels > bestVowels)
            {
                bestVowels = vowels;
                bestNumber = wordNumber;
                strcpy(bestWord, word);
            }
        }
    }
    fclose(f);

    cout << "\nСлово с наибольшим числом гласных:\n";
    cout << "  слово: " << bestWord << "\n";
    cout << "  номер слова в файле " << F2_NAME << ": " << bestNumber << "\n";
    cout << "  гласных букв: " << bestVowels << "\n";
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    setlocale(LC_ALL, "Russian");

    cout << "Лабораторная работа № 9. Строковый ввод-вывод\n";
    cout << "Вариант 22\n\n";

    createF1();
    printFile(F1_NAME);

    int copied = copyLongLines();
    if (copied < 0)
        return 1;
    cout << "\nВ файл " << F2_NAME << " скопировано строк: " << copied << "\n";
    printFile(F2_NAME);

    findWordWithMostVowels();
    return 0;
}
