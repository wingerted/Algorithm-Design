#include <iostream>

using namespace std;

/******************增量构造*******************
void Print_Subset(int P[], int cur) {
	int s;
	
	for (int i=1; i<=cur-1; i++) {
		cout << P[i] << " ";
	}
	cout << endl;

	if (cur == 0) {
		cout << "空" << endl;
		cur = 1;
		s = 1;
	} else {
		s = P[cur-1]+1;
	}

	for (int i=s; i<=P[0]; i++) {
		P[cur] = i;
		Print_Subset(P, cur+1);
	}	
}
**********************************************/

/******************位向量法*******************
void Print_Subset(int P[], int cur) {
	if (cur == 0) {
		cout << "空" << endl;
	}
	cur++;
	if (cur == P[0]+1) {
		for (int i=1; i<=P[0]; i++) {
			if (P[i] == 1) {
				cout << i << " ";
			}
		}
		cout << endl;
	} else {
		P[cur] = 1;
		Print_Subset(P, cur);

		P[cur] = 0;
		Print_Subset(P, cur);
	}
}
**********************************************/

void Print_Subset(int n) {  // 打印{0, 1, 2, ..., n-1}的子集S
	for(int i = 0; i < (1<<n); i++) { // 枚举各子集所对应的编码 0, 1, 2, ..., 2^n-1
		int s = i;
		
		for (int j=0; j<n; j++) {
			if (s & (1<<j)) {
				cout << j << " "; // 这里利用了C语言“非0值都为真”的规定
			}
		}
		cout << endl;
	}
}


int main()
{
	setlocale(LC_ALL, "");

	int result[100];

	cout << "输入N: " << endl;
	cin >> result[0];

//	Print_Subset(result, 0);

	Print_Subset(result[0]);

	return 0;
}