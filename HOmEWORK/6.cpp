#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "n = ";
    cin >> n;
    int a[100];
    cout << "array: ";
    for (int i = 0; i < n; i++) cin >> a[i];

    int i = 0;
    bool f = false;

    while (i < n - 1 && !f) {
        if (a[i] >= a[i + 1]) {
            f = true;
        }
        i++;
    }

    if (!f) {
        cout << "Массив упорядочен по возрастанию" << endl;
    } else {
        cout << "Массив НЕ упорядочен по возрастанию" << endl;
    }
    return 0;
}