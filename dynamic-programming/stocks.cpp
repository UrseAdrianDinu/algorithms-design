#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// Structura pentru a repezenta o actiune
struct Stock {
    int curr;
    int minval;
    int maxval;

    Stock(int _curr, int _minval, int _maxValue)
        : curr(_curr),
        minval(_minval), maxval(_maxValue) {}
};


class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, b, l;
    vector<Stock> stocks;
    // Citire fisier de intrare
    void read_input() {
        ifstream fin("stocks.in");
        fin >> n >> b >> l;
        for (int i = 0, curr, minval, maxval; i < n; i++) {
            fin >> curr >> minval >> maxval;
            stocks.push_back(Stock(curr, minval, maxval));
        }
        fin.close();
    }

    int get_result() {
        // dp[i][b][k] - reprezinta profitul maxim obtinut folosind
        // doar o parte din primele i actiuni,
        // bugetul maxim, si maxLoss = l
        vector<vector<vector<int>>> dp(n + 1,
        vector<vector<int>>(b + 1, vector<int>(l + 1, 0)));

        // Caz de baza (nu aleg nicio actiune)
        for (int j = 0; j <= b; ++j) {
            for (int k = 0; k <= l; ++k) {
                dp[0][j][k] = 0;
            }
        }

        // Cazul general
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= b; j++) {
                for (int k = 0; k <= l; k++) {
                    // Nu folosesc actiunea i, aleg cea mai buna
                    // solutie formata cu celelalte i - 1 elemente
                    dp[i][j][k] = dp[i - 1][j][k];
                    int d1 = j-stocks[i-1].curr;
                    int d2 = k - (stocks[i - 1].curr - stocks[i - 1].minval);
                    // Verific daca se poate cumpara actiunea i
                    if (d1 >= 0 && d2 >= 0) {
                        // Calculez profitul
                        int profit = stocks[i - 1].maxval - stocks[i - 1].curr;
                        // Il adun la solutia precedenta
                        int sol_aux = dp[i - 1][d1][d2] + profit;
                        // Maximizez solutia curenta
                        dp[i][j][k] = max(dp[i][j][k], sol_aux);
                    }
                }
            }
        }

        return dp[n][b][l];
    }

    // Scriere in fisierul de iesire
    void print_output(int result) {
        ofstream fout("stocks.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto *task = new (std::nothrow) Task{};
    if (!task) {
        std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
