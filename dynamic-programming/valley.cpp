#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    vector<int> valley;
    // Citire fisier de intrare
    void read_input() {
        ifstream fin("valley.in");
        fin >> n;
        for (int i = 0, x; i < n; i++) {
            fin >> x;
            valley.push_back(x);
        }
        fin.close();
    }

    long long int get_result() {
        // Gasesc pozitia minimului din vector
        int pos = min_element(valley.begin(), valley.end()) - valley.begin();

        long long int exc = 0LL;
        // Analizez cazul cand valea are 3 munti
        if (valley.size() == 3) {
            if (valley[1] > valley[2] && valley[2] < valley[0]) {
                return valley[1] - valley[2];
            }

            if (valley[1] > valley[0] && valley[1] < valley[2]) {
                return valley[1] - valley[0];
            }
        }

        // Parcurg vectorul pana la pozitia minimului - 1
        // si fac sapaturi astfel incat sa devina un sir descrescator
        for (int i = 0; i < pos - 1; i++) {
            if (valley[i] < valley[i + 1]) {
                exc += valley[i + 1] - valley[i];
                valley[i + 1] = valley[i];
            }
        }
        // Parcurg vectorul de la sfarsit pana la pozitia minimului + 1
        // si fac sapaturi astfel incat sa devina un sir crescator
        for (int i = n - 1; i >= pos + 1; i--) {
            if (valley[i] < valley[i - 1]) {
                exc += valley[i - 1] - valley[i];
                valley[i - 1] = valley[i];
            }
        }

        // Sir crescator
        if (exc == 0 && pos == 0) {
            return valley[1] - valley[0];
        }

        // Sir descrescator
        if (exc == 0 && pos == n - 1) {
            return valley[n - 2] - valley[n - 1];
        }
        return exc;
    }

    // Scriere in fisierul de iesire
    void print_output(long long int result) {
        ofstream fout("valley.out");
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
