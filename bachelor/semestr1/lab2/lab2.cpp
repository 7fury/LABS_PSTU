#include <iostream>
#include <iomanip>
#include <cmath>
#include <clocale>

using namespace std;

int main()
{
    setlocale(LC_ALL, ".65001");
    cout << fixed << setprecision(10);

    double sum = 0.0;

    cout << "Члены ряда:\n";

    for (int n = 2; n <= 16; ++n)
    {
        double ln_n = log(static_cast<double>(n));
        double a_n = pow(static_cast<double>(n), ln_n) / pow(ln_n, n);

        sum += a_n;

        cout << "n = " << setw(2) << n
             << "  a_n = " << a_n << "\n";
    }

    cout << "\nСумма 15 членов ряда = " << sum << "\n";

    return 0;
}
