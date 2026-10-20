#include <iostream>
#include <cmath>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, ".65001");
    double a, b, c, D, x1, x2;
    cout << "Введите a, b, c: ";
    cin >> a >> b >> c;

    if (a == 0) {
        // Линейное уравнение bx + c = 0 (логика из задачи 2)
        if (b == 0) {
            if (c == 0) cout << "Бесконечно много решений";
            else cout << "Нет решений";
        } else {
            x1 = -c / b;
            cout << "x = " << x1;
        }
    } else {
        D = b*b - 4*a*c;
        if (D > 0) {
            x1 = (-b + sqrt(D)) / (2*a);
            x2 = (-b - sqrt(D)) / (2*a);
            cout << "x1 = " << x1 << "; x2 = " << x2;
        } else if (D == 0) {
            x1 = -b / (2*a);
            cout << "x = " << x1;
        } else {
            cout << "Корней нет";
        }
    }
    return 0;
}