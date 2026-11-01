#include <iostream>
#include <clocale>
using namespace std;

const int MAX_SIZE = 100;

bool isEmpty(int top)
{
    return top == -1;
}

bool isFull(int top)
{
    return top == MAX_SIZE - 1;
}

void printStack(const int stack[], int top)
{
    cout << "Текущий стек: ";
    if (isEmpty(top))
    {
        cout << "(пуст)" << endl;
        return;
    }

    for (int i = 0; i <= top; ++i)
    {
        cout << stack[i] << " ";
    }
    cout << endl;
}

bool push(int stack[], int &top, int value)
{
    if (isFull(top))
    {
        cout << "Ошибка: стек полон, добавление невозможно." << endl;
        return false;
    }

    top++;
    stack[top] = value;
    cout << "Добавлен элемент " << value << "." << endl;
    return true;
}

bool pop(int stack[], int &top, int &value)
{
    if (isEmpty(top))
    {
        cout << "Ошибка: стек пуст, удаление невозможно." << endl;
        return false;
    }

    value = stack[top];
    top--;
    cout << "Удалён элемент " << value << "." << endl;
    return true;
}

int main()
{
    setlocale(LC_ALL, ".65001");


    int stack[MAX_SIZE];
    int top = -1;
    int choice;

    do
    {
        cout << "\nМеню:" << endl;
        cout << "1 - добавить элемент (push)" << endl;
        cout << "2 - удалить элемент (pop)" << endl;
        cout << "3 - напечатать стек" << endl;
        cout << "0 - выход" << endl;
        cout << "Выберите пункт: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int value;
            cout << "Введите значение: ";
            cin >> value;
            push(stack, top, value);
            printStack(stack, top);
            break;
        }
        case 2:
        {
            int value;
            pop(stack, top, value);
            printStack(stack, top);
            break;
        }
        case 3:
            printStack(stack, top);
            break;
        case 0:
            cout << "Завершение работы." << endl;
            break;
        default:
            cout << "Неверный пункт меню." << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}