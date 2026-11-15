#include <iostream>
#include <cstring>
#include <cctype>
#include <clocale>

using namespace std;

const int MAX_LEN = 256;
const int MAX_WORDS = 64;

// Безопасный аналог функции gets: читает строку целиком, включая пробелы
void Gets(char* s, int size)
{
    cin.getline(s, size);
}

// Проверка, является ли символ разделителем слов
bool isSeparator(char c)
{
    return c == '_' || c == ' ' || c == '\t';
}

// Звук, которым передаётся английская буква
const char* letterSound(char c)
{
    switch (toupper(static_cast<unsigned char>(c)))
    {
    case 'A': return "э";
    case 'B': return "б";
    case 'C': return "с";
    case 'D': return "д";
    case 'E': return "э";
    case 'F': return "ф";
    case 'G': return "г";
    case 'H': return "";
    case 'I': return "и";
    case 'J': return "ж";
    case 'K': return "к";
    case 'L': return "л";
    case 'M': return "м";
    case 'N': return "н";
    case 'O': return "о";
    case 'P': return "п";
    case 'Q': return "к";
    case 'R': return "р";
    case 'S': return "с";
    case 'T': return "т";
    case 'U': return "у";
    case 'V': return "в";
    case 'W': return "в";
    case 'X': return "кс";
    case 'Y': return "и";
    case 'Z': return "з";
    default:  return "";
    }
}

// Запись "произношения" слова в строку result
void pronounceWord(const char* word, char* result)
{
    result[0] = '\0';

    for (int i = 0; word[i] != '\0'; ++i)
        if (isalpha(static_cast<unsigned char>(word[i])))
            strcat(result, letterSound(word[i]));
}

// Разбиение строки на слова по символам '_' и пробелам
int splitIntoWords(char* text, char words[][MAX_LEN], int maxWords)
{
    int len = static_cast<int>(strlen(text));

    // Удаляем завершающую точку и пробелы в конце
    while (len > 0 &&
           (text[len - 1] == '.' ||
            isspace(static_cast<unsigned char>(text[len - 1]))))
    {
        text[--len] = '\0';
    }

    int count = 0;
    int i = 0;

    while (text[i] != '\0' && count < maxWords)
    {
        while (text[i] != '\0' && isSeparator(text[i]))
            ++i;

        if (text[i] == '\0')
            break;

        int j = 0;
        while (text[i] != '\0' && !isSeparator(text[i]) && j < MAX_LEN - 1)
            words[count][j++] = text[i++];

        words[count][j] = '\0';
        ++count;
    }

    return count;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    char text[MAX_LEN];

    cout << "Введите предложение на английском языке\n";
    cout << "(слова через '_' или пробел, в конце точка):\n";
    Gets(text, MAX_LEN);

    char words[MAX_WORDS][MAX_LEN];
    int n = splitIntoWords(text, words, MAX_WORDS);

    char result[MAX_LEN] = "";

    for (int i = 0; i < n; ++i)
    {
        char proposed[MAX_LEN];
        pronounceWord(words[i], proposed);

        cout << "\nСлово \"" << words[i] << "\" -> \""
             << (proposed[0] != '\0' ? proposed : "(без звуков)") << "\"\n";
        cout << "Enter - принять, иначе введите свой вариант: ";

        char answer[MAX_LEN];
        Gets(answer, MAX_LEN);

        if (answer[0] == '\0')
        {
            cout << "Принято: " << proposed << "\n";
            strcat(result, proposed);
        }
        else
        {
            cout << "Ваш вариант: " << answer << "\n";
            strcat(result, answer);
        }

        if (i + 1 < n)
            strcat(result, " ");
    }

    cout << "\nРезультат: " << result << "\n";

    return 0;
}
