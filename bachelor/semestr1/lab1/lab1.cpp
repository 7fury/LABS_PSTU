#include <iostream>
#include <iomanip>
#include <clocale>
using namespace std;

template <typename T>
void calculate(const char* typeName) {
    T a = 100.0, b = 0.001;

    T aMinusB = a - b;
    T square = aMinusB * aMinusB;
    T fourthPower = square * square;
    T a2 = a * a;
    T a3 = a2 * a;
    T a4 = a2 * a2;
    T b2 = b * b;
    T b3 = b2 * b;
    T b4 = b2 * b2;
 
    T numerator = fourthPower - (a4 - 4 * a3 * b);
    T denominator = 6 * a2 * b2 - 4 * a * b3 + b4;
    T result = numerator / denominator;


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

    return 0;
}