#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// Structura pentru a repezenta un calculator
struct Computer {
    double power;
    double upgrade_cost;

    Computer(int _power, int _upgrade_cost)
        : power(_power), upgrade_cost(_upgrade_cost) {}
};

// Comparator folosit pentru a sorta calculatoarele in priority_queue
// Sortare crescatoare dupa cost, iar in cazul in care 2
// calculatoare au aceeasi putere, se sorteaza crescator
// dupa upgrade cost
class myComparator {
 public:
    int operator()(const Computer &a, const Computer &b) {
        if (a.power == b.power) {
            return a.upgrade_cost > b.upgrade_cost;
        } else {
            return a.power > b.power;
        }
    }
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, b;
    priority_queue<Computer, vector<Computer>, myComparator> computers;
    // Citire fisier de intrare
    void read_input() {
        ifstream fin("crypto.in");
        fin >> n >> b;
        for (int i = 0, power, cost; i < n; i++) {
            fin >> power >> cost;
            computers.push(Computer(power, cost));
        }
        fin.close();
    }

    int get_result() {
        while (b > 0 && computers.empty() == false && computers.size() >= 2) {
            // Extrag din coada primele 2 calculatoare cu putere minima
            Computer c1 = computers.top();
            computers.pop();
            Computer c2 = computers.top();
            computers.pop();
            int upgrade = c1.upgrade_cost + c2.upgrade_cost;
            // Daca calculatorul al doilea are puterea mai mare
            if (c2.power > c1.power) {
                // Calculez costul de upgrade
                int cost = (c2.power - c1.power) * c1.upgrade_cost;
                // Verific daca se poate face upgrade-ul
                if (b - cost >= 0) {
                    // Actualizez banii
                    b -= cost;
                    computers.push(Computer(c2.power, upgrade));
                } else {
                    return c1.power + b/c1.upgrade_cost;
                }
            } else {
                computers.push(Computer(c1.power, upgrade));
            }
        }
        return computers.top().power + b/computers.top().upgrade_cost;
    }

    // Scriere in fisierul de iesire
    void print_output(int result) {
        ofstream fout("crypto.out");
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
