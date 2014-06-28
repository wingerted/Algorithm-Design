#include <iostream>

using namespace std;
/*
void BackTrack(int n, int candidate[], int result[], int p) {
	for (int i=1; i<=n; i++) {
		if (candidate[i] == 1) {
			continue;
		} else {
			candidate[i] = 1;
			result[p] = i;
			BackTrack(n, candidate, result, p+1);
			candidate[i] = 0;
		}
	}

	if (p != n-1) {
		return;
	}

	for (int i=0; i<n; i++) {
		cout << result[i] << " ";
	}
	cout << endl;
}
*/

void Print_Permutation(int n, int result[], int cur) {
	if (cur == n) {
		for (int i=0; i<n; i++) {
			cout << result[i] << " ";
		}
		cout << endl;
	} else {
		for (int i=1; i<=n; i++) {
			bool key = true;
			
			for (int j=0; j<cur; j++) {
				if (result[j] == i) {
					key = false;
				}
			}

			if (key) {
				result[cur] = i;
				Print_Permutation(n, result, cur+1);
			}			
		}
	}
}


int main()
{
	setlocale(LC_ALL, "");
	
	int n;
//	int candidate[100];
//	memset(candidate, 0, sizeof(candidate));	
	int result[100];


	cout << "ÇëÊäÈëN£º" << endl;
	cin >> n;

	Print_Permutation(n, result, 0);

//	BackTrack(n, candidate, result, 0);

	return 0;
}