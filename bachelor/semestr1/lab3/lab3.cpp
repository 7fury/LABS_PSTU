#include <iostream>
#include <iomanip>
#include <cmath>
#include <clocale>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    const double a = 0.1;
    const double b = 1.0;
    const int K = 10;
    const int N = 35;
    const double eps = 1e-4;

    double h = (b - a) / K;

    cout << fixed << setprecision(6);
    cout << "X\tSN\tSE\tY\n";

    for (int i = 0; i <= K; ++i)
    {
        double x = a + i * h;

        // Сумма для заданного n = 35
        double SN = 0.0;
        double termN = 1.0; // a_0

        for (int n = 0; n <= N; ++n)
        {
            SN += termN;

            termN *= -((2.0 * n * n + 4.0 * n + 3.0) * x * x) /
                     ((2.0 * n * n + 1.0) * (2.0 * n + 1.0) * (2.0 * n + 2.0));
        }


        double SE = 0.0;
        double termE = 1.0; // a_0
        int n = 0;

        while (fabs(termE) >= eps && n < 10000)
        {
            SE += termE;

            termE *= -((2.0 * n * n + 4.0 * n + 3.0) * x * x) /
                     ((2.0 * n * n + 1.0) * (2.0 * n + 1.0) * (2.0 * n + 2.0));

            ++n;
        }

        double Y = (1.0 - x * x / 2.0) * cos(x) - (x / 2.0) * sin(x);

        cout << x << "\t" << SN << "\t" << SE << "\t" << Y << "\n";
    }

    return 0;
}
