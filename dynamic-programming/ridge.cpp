#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// Structura pentru a repezenta un munte
struct Mountain {
    long long int h;
    long long int c;

    Mountain(int _h, int _c)
        : h(_h), c(_c) {}
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    long long int n;
    vector<Mountain> ridge;

    // Citire fisier de intrare
    void read_input() {
        ifstream fin("ridge.in");
        fin >> n;
        for (int i = 0, h, c; i < n; i++) {
            fin >> h >> c;
            ridge.push_back(Mountain(h, c));
        }
        fin.close();
    }

    long long int get_result() {
        // dp[i][j] - reprezinta costul minim necesar pentru a face
        // muntele i distinct fata de muntii de langa el, facand j sapaturi
        // in el
        // Maximul de sapaturi necesare pentru a face muntii
        // consecutivi distincti este 2
        vector<vector<long long int>> dp(n + 1, vector<long long int>(3));

        // Cazul de baza se fac j = 0..2 in primul munte
        dp[0][0] = 0;
        dp[0][1] = ridge[0].c;
        dp[0][2] = ridge[0].c * 2;

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < 3; j++) {
            long long int temp = LONG_LONG_MAX;
            // Verific daca se pot face j sapaturi in muntele curent
            if ( ridge[i].h - j >= 0 ) {
                // Verific daca prin j sapaturi in muntele curent sa nu
                // fie egal cu muntele precedent
                if ( ridge[i].h - j != ridge[i - 1].h ) {
                    temp = min(temp, dp[i - 1][0]);
                }

                if (ridge[i].h - j != ridge[i - 1].h - 1) {
                    temp = min(temp, dp[i - 1][1]);
                }

                if (ridge[i].h - j != ridge[i - 1].h - 2) {
                    temp = min(temp, dp[i - 1][2]);
                }

                dp[i][j] = j * ridge[i].c + temp;
            } else {
                dp[i][j] = temp;
            }
        }
    }

    // Costul minim este minimul din penultima linie a matricei dp
    long long int mincost = *std::min_element(dp[n-1].begin(), dp[n-1].end());
    return mincost;
    }

    // Scriere in fisierul de iesire
    void print_output(long long int result) {
        ofstream fout("ridge.out");
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
