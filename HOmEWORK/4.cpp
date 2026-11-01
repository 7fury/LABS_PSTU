#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int a[2][3];
    cout << "Enter 2x3 matrix:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> a[i][j];
        }
    }

    int s0 = 0, s1 = 0;
    for (int j = 0; j < 3; j++) {
        s0 += a[0][j];
        s1 += a[1][j];
    }

    cout << "Matrix:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(5) << a[i][j];
        }
        cout << endl;
    }

    cout << "Sum row 1 = " << s0 << endl;
    cout << "Sum row 2 = " << s1 << endl;
    return 0;
}