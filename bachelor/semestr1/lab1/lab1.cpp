#include <iostream>
#include <iomanip>
#include <cmath>
#include <clocale>
using namespace std;

template <typename T>
void calculate(const char* typeName) {
    T a = 100.0, b = 0.001;

    T numerator   = (a - b)*(a - b)*(a - b)*(a - b) - (a*a*a*a - 4*a*a*a*b);
    T denominator = 6*a*a*b*b - 4*a*b*b*b + b*b*b*b;
    T result      = numerator / denominator;

    cout << "\nТип данных: " << typeName << '\n'
         << "Числитель = " << numerator << '\n'
         << "Знаменатель = " << denominator << '\n'
         << "Результат = " << result << '\n';
}

int main() {
    setlocale(LC_ALL, ".65001");
    cout << fixed << setprecision(10);

    calculate<float>("float");
    calculate<double>("double");
}