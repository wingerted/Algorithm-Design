#include <iostream>

using namespace std;

void permutation(int m, int n, int candidates[], int result[], int p) {
	for (int i=1; i<=m; i++) {
		if (candidates[i] == 1) {
			continue;
		} else {
			result[p] = i; 
			candidates[i] = 1;
			if (p == n-1) {
				for (int j=0; j<n; j++) {
					cout << result[j] << " ";
				}
				cout << endl;

				candidates[i] = 0;
				continue;
			}
			permutation(m, n, candidates, result, p+1);
			candidates[i] = 0;
		}
	}
}
	
void combination(int m, int n, int result[], int p) {
	for (int i=m; i>=1; i--) {
		result[p] = i; 
			
		if (p == n-1) {
			for (int j=0; j<n; j++) {
				cout << result[j] << " ";
			}
			cout << endl;
			continue;
		}
			combination(i-1, n, result, p+1);
	}	
}


int main()
{
	setlocale(LC_ALL, "");

	int n, m;
	int candidates[100];
	int result[100];

	memset(candidates, 0, sizeof(candidates));
	memset(result, 0, sizeof(result));

	cout << "请输入总数M和选取数N：" << endl;
	cin >> m >> n;

	cout << "排列为：" << endl;
	permutation(m, n, candidates, result, 0);

	cout << "组合为：" << endl;
	combination(m, n, result, 0);
	
	return 0;
}
