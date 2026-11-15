#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdarg>
#include <clocale>

using namespace std;

const double PI = acos(-1.0);

// Площадь треугольника по трём сторонам (формула Герона)
double triangleArea(double a, double b, double c)
{
    if (a <= 0.0 || b <= 0.0 || c <= 0.0)
        return 0.0;

    if (a + b <= c || a + c <= b || b + c <= a)
        return 0.0;

    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

// Сумма центральных углов для многоугольника,
// вписанного в окружность радиуса R
double angleSum(const double* sides, int n, double R)
{
    double sum = 0.0;

    for (int i = 0; i < n; ++i)
        sum += 2.0 * asin(sides[i] / (2.0 * R));

    return sum;
}

// Площадь многоугольника, вписанного в окружность,
// по заданным длинам сторон
double cyclicPolygonArea(const double* sides, int n)
{
    double maxSide = sides[0];
    double perimeter = 0.0;

    for (int i = 0; i < n; ++i)
    {
        if (sides[i] <= 0.0)
            return 0.0;

        if (sides[i] > maxSide)
            maxSide = sides[i];

        perimeter += sides[i];
    }

    // Проверка неравенства многоугольника
    if (maxSide >= perimeter - maxSide)
        return 0.0;

    // Ищем радиус описанной окружности R:
    // сумма центральных углов должна быть равна 2*PI
    double lo = maxSide / 2.0 + 1e-12;
    double hi = perimeter;

    while (angleSum(sides, n, hi) > 2.0 * PI && hi < 1e12)
        hi *= 2.0;

    for (int it = 0; it < 200; ++it)
    {
        double mid = (lo + hi) / 2.0;

        if (angleSum(sides, n, mid) > 2.0 * PI)
            lo = mid;
        else
            hi = mid;
    }

    double R = (lo + hi) / 2.0;
    double area = 0.0;

    for (int i = 0; i < n; ++i)
    {
        double angle = 2.0 * asin(sides[i] / (2.0 * R));
        area += 0.5 * R * R * sin(angle);
    }

    return area;
}

// Функция с переменным числом параметров:
// площадь n-угольника по n заданным сторонам
double square(int n, ...)
{
    if (n < 3 || n > 32)
        return 0.0;

    double sides[32];

    va_list ap;
    va_start(ap, n);

    for (int i = 0; i < n; ++i)
        sides[i] = va_arg(ap, double);

    va_end(ap);

    // Для треугольника используем формулу Герона
    if (n == 3)
        return triangleArea(sides[0], sides[1], sides[2]);

    // Для n >= 4 считаем многоугольник вписанным в окружность
    return cyclicPolygonArea(sides, n);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << fixed << setprecision(4);

    cout << "Площадь треугольника со сторонами 3, 4, 5: "
         << square(3, 3.0, 4.0, 5.0) << "\n";

    cout << "Площадь пятиугольника со сторонами 5, 5, 5, 5, 5: "
         << square(5, 5.0, 5.0, 5.0, 5.0, 5.0) << "\n";

    cout << "Площадь восьмиугольника со сторонами 4, 4, 4, 4, 4, 4, 4, 4: "
         << square(8, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0) << "\n";

    return 0;
}
