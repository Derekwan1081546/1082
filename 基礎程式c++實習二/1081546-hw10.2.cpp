#include<iostream>

using namespace std;

#define maxn 15

int A[maxn][maxn];

void First() {
	int i, k;
	for (i = 0; i < 7; i += 2) {
		k = A[6][i] - (A[8][i] + A[8][i + 2]);
		A[8][i + 1] = k / 2;
	}
}


void Finish() {
	int i, j;
	for (i = 7; i >= 1; i--) {
		for (j = 0; j <= i; j++) {
			A[i][j] = A[i + 1][j] + A[i + 1][j + 1];
		}
	}
}

//#include<stdio.h>

int main() {
	int ks, i, j;
	//	freopen("c:\\h.txt","r",stdin);
	cin >> ks;
	while (ks--) {
		for (i = 0; i <= 8; i += 2) {
			for (j = 0; j <= i; j += 2) {
				cin >> A[i][j];
			}
		}
		First();
		Finish();
		for (i = 0; i < 9; i++) {
			cout << A[i][0];
			for (j = 1; j <= i; j++) {
				cout << " " << A[i][j];
			}
			cout << endl;
		}
	}
	return 0;

}