#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "n = ";
    cin >> n;
    int a[100];
    cout << "array: ";
    for (int i = 0; i < n; i++) cin >> a[i];

    int max = a[0], min = a[0];
    int imax = 0, imin = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] > max) { max = a[i]; imax = i; }
        if (a[i] < min) { min = a[i]; imin = i; }
    }

    int cntMax = 0, cntMin = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == max) cntMax++;
        if (a[i] == min) cntMin++;
    }

    cout << "max = " << max << ", min = " << min << endl;
    cout << "first max: number = " << imax + 1 << ", index = " << imax << endl;
    cout << "first min: number = " << imin + 1 << ", index = " << imin << endl;
    cout << "count max = " << cntMax << ", count min = " << cntMin << endl;
    return 0;
}