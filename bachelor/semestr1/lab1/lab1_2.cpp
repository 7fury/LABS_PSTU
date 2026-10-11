#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, ".65001");
    int n = 2, m = 1;
    cout << "Начальные значения: n = " << n << ", m = " << m << endl;

    // 1) ++n * ++m
    int n1 = n, m1 = m;
    int res1 = ++n1 * ++m1;
    cout << "++n * ++m = " << res1
         << " (n = " << n1 << ", m = " << m1 << ")" << endl;

    // 2) m++ < n
    int n2 = n, m2 = m;
    bool res2 = (m2++ < n2);
    cout << "m++ < n = " << boolalpha << res2
         << " (n = " << n2 << ", m = " << m2 << ")" << endl;

    // 3) n++ > m
    int n3 = n, m3 = m;
    bool res3 = (n3++ > m3);
    cout << "n++ > m = " << boolalpha << res3
         << " (n = " << n3 << ", m = " << m3 << ")" << endl;

    return 0;
}

