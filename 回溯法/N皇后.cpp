/*****************************************************************
#include <iostream>

using namespace std;

void Queen(int n, int c, bool cur[][100], int &tot) {
	if (c == n) {
		tot++;
	} else {
		for (int i=0; i!=n; ++i) {
			if (!cur[0][i] && !cur[1][i+c] && !cur[2][c-i+n]) {
				cur[0][i] = cur[1][i+c] = cur[2][c-i+n] = 1;
				Queen(n, c+1, cur, tot);
				cur[0][i] = cur[1][i+c] = cur[2][c-i+n] = 0;
			}
		}
	}
}


int main()
{
	setlocale(LC_ALL, "");
	int n;
	int tot = 0;
	bool cur[3][100] = {0};

	cout << "ÇëÊäÈëN£º" << endl;
	cin >> n;

	Queen(n, 0, cur, tot);

	cout << tot << endl;

	return 0;
}

*************************************************************/

/*****************************************************************


#include <iostream>

using namespace std;

typedef struct Row {
	int next[100];
	int pre[100];
}Row;

Row r;

void Queen(int n, int c, bool cur[][100], int &tot) {
	if (c == n+1) {
		tot++;
	} else {
		for (int i=r.next[0]; i!=n+1; i=r.next[i]) {
			if (!cur[0][i+c] && !cur[1][c-i+n]) {
				r.next[r.pre[i]]=r.next[i]; 
				r.pre[r.next[i]]=r.pre[i];
				
				cur[0][i+c] = cur[1][c-i+n] = 1;
				Queen(n, c+1, cur, tot);
				
				r.next[r.pre[i]]=i; 
				r.pre[r.next[i]]=i;
				
				cur[0][i+c] = cur[1][c-i+n] = 0;
			}
		}
	}
}


int main()
{
	setlocale(LC_ALL, "");
	int n;
	int tot = 0;
	bool cur[2][100] = {0};

	cout << "ÇëÊäÈëN£º" << endl;
	cin >> n;

	for (int i=1; i<=n+1; ++i) {
		r.pre[i] = i-1;
		r.next[i] = i+1;
	}

	r.pre[n+2]=n+1; 
	r.next[0]=1;


	Queen(n, 1, cur, tot);

	cout << tot << endl;

	return 0;
}

*************************************************************/




#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Row {
	int next[100];
	int pre[100];
}Row;

int site[100] = {0};

void Queen(int n, int c, bool cur[][100], int &tot) {
	if (c == n+1) {
		tot++;
	} else {
		Row r;

		for (int i=1; i<=n+1; ++i) {
			r.pre[i] = i-1;
			r.next[i] = i+1;
		}

		r.pre[n+2]=n+1; 
		r.next[0]=1;

		for(int j=1; j!=c; ++j)
		{
			int rr = site[j];
			if (r.next[r.pre[rr]] < r.next[rr]) {
				r.next[r.pre[rr]]=r.next[rr]; 
				r.pre[r.next[rr]]=r.pre[rr];
			}
			if (site[j]-(c-j) > 0) {
				int x = site[j]-(c-j);
				if (r.next[r.pre[x]] < r.next[x]) {
					r.next[r.pre[x]]=r.next[x]; 
					r.pre[r.next[x]]=r.pre[x];
				}
			}
			if (site[j]+(c-j) <= n) {
				int x = site[j]+(c-j);
				if (r.next[r.pre[x]] < r.next[x]) {
					r.next[r.pre[x]]=r.next[x]; 
					r.pre[r.next[x]]=r.pre[x];
				}
			}
		}

		for (int i=r.next[0]; i!=n+1; i=r.next[i]) {
				
			site[c] = i;
				
			Queen(n, c+1, cur, tot);
				
	
		}
	}
}


int main()
{
	setlocale(LC_ALL, "");
	int n;
	int tot = 0;
	bool cur[2][100] = {0};

	cout << "ÇëÊäÈëN£º" << endl;
	cin >> n;

	


	Queen(n, 1, cur, tot);

	cout << tot << endl;

	return 0;
}
