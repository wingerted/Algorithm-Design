#include <iostream>

using namespace std;

void Print(int a, int b, int c, int d, int e, int f) {
	cout << "  " << a << "  " << endl;
	cout << " " << b << " " << f << endl;
	cout << c << " " << d << " " << e << endl << endl;
}

void Print_Triangle(int n) {
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=n; j++) {
			for (int k=1; k<=n; k++) {
				for (int l=1; l<=n; l++) {
					for (int m=1; m<=n; m++) {
						for (int o=1; o<=n; o++) {
							if (i == j || i == k ||
								i == l || i == m ||
								i == o || j == k ||
								j == l || j == m ||
								j == o || k == l ||
								k == m || k == o ||
								l == m || l == o ||
								m == o) {
									continue;
							} else if (i+j+k == k+l+m &&
									   i+j+k == m+o+i) {
										   Print(i, j, k, l, m, o);
							}
						}
					}
				}
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "ÊäÈëÔªËØ·¶Î§£º" << endl;
	cin >> n;

	Print_Triangle(n);

	return 0;
}