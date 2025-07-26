#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define MOD 1000000007
ifstream fin("trigigel.in");
ofstream fout("trigigel.out");
#define KMAX 4

// Functie preluata din laboratorul 4, pentru inmultirea matricilor
// C = A * B
void multiply_matrix(long long int A[KMAX][KMAX],
    long long int B[KMAX][KMAX], long long int C[KMAX][KMAX]) {
    long long int tmp[KMAX][KMAX];
    // tmp = A * B
    for (int i = 0; i < KMAX; ++i) {
        for (int j = 0; j < KMAX; ++j) {
            long long int sum = 0;
            for (int k = 0; k < KMAX; ++k) {
                sum += 1LL * A[i][k] * B[k][j];
            }
            tmp[i][j] = sum % MOD;
        }
    }

    //  C = tmp
    memcpy(C, tmp, sizeof(tmp));
}

// Functie preluata din laboratorul 4, pentru exponențiere
// logaritmică pe matrice
// R = C^p
void power_matrix(long long int C[KMAX][KMAX],
    long long int p, long long int R[KMAX][KMAX]) {
    // tmp = I (matricea identitate)
    long long int tmp[KMAX][KMAX];
    for (int i = 0; i < KMAX; ++i) {
        for (int j = 0; j < KMAX; ++j) {
            tmp[i][j] = (i == j) ? 1 : 0;
        }
    }

    while (p != 1) {
        if (p % 2 == 0) {
            multiply_matrix(C, C, C);  // C = C*C
            p /= 2;                    // rămâne de calculat C^(p/2)
        } else {
            // reduc la cazul anterior:
            multiply_matrix(tmp, C, tmp);  // tmp = tmp*C
            --p;                           // rămâne de calculat C^(p-1)
        }
    }

    // avem o parte din rezultat în C și o parte în tmp
    multiply_matrix(C, tmp, R);  // rezultat = tmp * C
}

int main() {
    long long int n;
    // Recurenta liniara dp[i] = dp[i-1] + dp[i-3] + 3
    long long int C[4][4] = {{1, 0, 1, 1},
                            {1, 0, 0, 0},
                            {0, 1, 0, 0},
                            {0, 0, 0, 1}};
    fin >> n;
    // Pentru n <= 4 , numarul de subsiruri ce se pot forma din
    // sirul initial este (n (n+1))/2
    if (n <= 4) {
        fout << (n * (n + 1)) / 2;
        return 0;
    }
    // S4 = (dp[4], dp[3], dp[2], 3) = (10, 6, 3, 3)
    // C = C^(n-4)
    power_matrix(C, n - 4, C);
    // sol = S_4 * C
    long long int sol = 10 * C[0][0] + 6 * C[0][1] + 3 * C[0][2] + 3 * C[0][3];
    sol = sol % MOD;
    fout << sol;

    return 0;
}
