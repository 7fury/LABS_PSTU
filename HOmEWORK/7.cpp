#include <iostream>
using namespace std;

int main() {
    int r, c;
    cout << "rows cols = ";
    cin >> r >> c;
    int a[100][100];
    cout << "matrix:" << endl;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> a[i][j];
        }
    }

    int max = a[0][0];
    int imax = 0, jmax = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i][j] > max) {
                max = a[i][j];
                imax = i;
                jmax = j;
            }
        }
    }

    cout << "max = " << max << endl;
    cout << "index = [" << imax << "][" << jmax << "]" << endl;
    return 0;
}