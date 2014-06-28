#include <iostream>

using namespace std;

void Print_Permutation(int n, int result[], int P[], int cur) {
	if (cur == n+1) {
		for (int i=1; i<=n; i++) {
			cout << result[i] << " ";
		}
		cout << endl;
		return ;
	}

	for (int i=1; i<=n; i++) { 
		bool key = true;
		for (int j=1; j<i; j++) {
			if (P[j] == P[i]) {
				key = false;
			}
		}
		
		if (key) {
			int count1 = 0;
			int count2 = 0;
		
			for (int j=1; j<cur; j++) {	
				if (result[j] == P[i]) {
					count1++;
				}
			}
			for (int j=1; j<=n; j++) {
				if (P[j] == P[i]) {
					count2++;
				}
			}
	
			if (count1 < count2) {
				result[cur] = P[i];
				Print_Permutation(n, result, P, cur+1);
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "");
	int i = 1;
	int P[100];
	int result[100];

	cout << "输入数字序列(输入-999结束)" << endl;
	cin >> P[0];

	while (P[0] != -999) {
		P[i++] = P[0];
		cin >> P[0];
	}

	Print_Permutation(i-1, result, P, 1);

	return 0;
}