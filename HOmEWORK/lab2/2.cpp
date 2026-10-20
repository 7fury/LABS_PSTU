#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, ".65001");
    double a, b, x;
    cout << "Введите a и b: ";
    cin >> a >> b;

    if (a == 0) {
        if (b == 0) {
            cout << "Бесконечно много решений";
        } else {
            cout << "Нет решений";
        }
    } else {
        x = -b / a;
        cout << "x = " << x;
    }
    return 0;
}