#include <iostream>
#define N 3
#define MAX 12

using namespace std;

int table[N+2][N+2];
int candidate[MAX+1];


void PrintTable() {
	for (int i=1; i<=N; i++){
		for (int j=1; j<=N; j++){
			cout << table[i][j] << ' ';
		}
		cout << endl;
	}

	cout << endl;
}

bool Prime(int n) {
	for (int i=2; i<n/2; i++) {
		if (n%i == 0) {
			return false;
		}
	}

	return true;
}


int Judge(int x, int y, int i){
	if (x==0 || x==N+1 || y==0 || y==N+1 || candidate[i]==1) {
		return 0;
	} else if ((table[x][y+1]==0 || Prime(table[x][y+1]+i)) &&
		(table[x][y-1]==0 || Prime(table[x][y-1]+i)) &&
		(table[x+1][y]==0 || Prime(table[x+1][y]+i)) &&
		(table[x-1][y]==0 || Prime(table[x-1][y]+i))
		) {
			table[x][y] = i;
			return 1;
	}

	return 0;
}


void backtrack(int x, int y){
	if (table[N][N] != 0) {
		PrintTable();
	}

	for (int i=1; i<=MAX; i++){
		if (Judge(x, y, i) == 1) {	
			candidate[i] = 1;

			table[x][y] = i;

			if (y < N) {
				backtrack(x, y+1);
			} else {
				backtrack(x+1, 1);
			}
		}
	}

	if (y > 1){
		candidate[table[x][y-1]] = 0;
		table[x][y-1] = 0;
	} else {
		candidate[table[x-1][N]] = 0;
		table[x-1][N] = 0;
	}
}



int main()
{
	freopen("data.txt", "w", stdout);	

	memset(table, 0, sizeof(table));
	
	memset(candidate, 0, sizeof(candidate));

	backtrack(1, 1);

	return 0;
}