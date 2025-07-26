#include <bits/stdc++.h>
#include <iostream>
using namespace std;

ifstream fin("poduri.in");
ofstream fout("poduri.out");

// structura pentru a defini o coordonata pe matrice
struct poz {
    int x, y;

    poz() {
    }

    poz(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, m;
    // pozitia de start
    int STARTX, STARTY;
    char matrix[2053][2053];

    // deplasari pentru pod de tip D
    const int podDx[4] = {-1, 1, 0, 0};
    const int podDy[4] = {0, 0, -1, 1};

    // deplasari pentru pod de tip O
    int podO[2] = {1, -1};
     // deplasari pentru pod de tip V
    int podV[2] = {1, -1};

    // Citire fisier de intrare
    void read_input() {
        fin >> n >> m;
        fin >> STARTX >> STARTY;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                fin >> matrix[i][j];
            }
        }
        fin.close();
    }

    // functia care verifica pentru o pozitie data
    // daca este pe marginea tablei
    // si daca se poate ajunge pe uscat din acea pozitie
    int Bord(int x, int y) {
        if (x == 1 && (matrix[x][y] == 'V' || matrix[x][y] == 'D'))
            return 1;
        if (y == 1 && (matrix[x][y] == 'O' || matrix[x][y] == 'D'))
            return 1;
        if (x == n && (matrix[x][y] == 'V' || matrix[x][y] == 'D'))
            return 1;
        if (y == m && (matrix[x][y] == 'O' || matrix[x][y] == 'D'))
            return 1;
        return 0;
    }

    // functie care verifica daca o pozitie este in interiorul tablei
    int checkInside(int x, int y) {
        if (x >= 1 && x <= n && y >= 1 && y <= m)
            return 1;
        return 0;
    }

    int bfs(int a, int b) {
        // alocare matice de distante
        // d[i][j] = INT_MAX, oricare ar fi i si j
        vector<vector<int>> d(n + 1, vector<int>(m + 1, INT_MAX));

        // coada de pozitii
        queue<poz> q;

        // Pun pozitia initiala in coada
        q.push({a, b});

        d[a][b] = 0;

        // Reprezinta minimul de poduri traversate
        int min = INT_MAX;

        // Cat timp NU am parcurs toate pozitiile
        while (!q.empty()) {
            // Extrag si procesez urmatorea pozitie din coada
            poz p = q.front();
            q.pop();

            // Daca pe pozitia curenta este pod de tip D,
            // parcurg vectorul de deplari, creez coordonate noi.
            if (matrix[p.x][p.y] == 'D') {
                for (int i = 0; i < 4; i++) {
                    int xnou = p.x + podDx[i];
                    int ynou = p.y + podDy[i];
                    // Verific daca coordonatele noi sunt in interiorul tablei
                    if (checkInside(xnou, ynou) == 1) {
                        // Actualizez distanta pana la pozitia xnou,ynou
                        // daca am gasit o solutie mai buna
                        if (d[p.x][p.y] + 1 < d[xnou][ynou]) {
                            d[xnou][ynou] = d[p.x][p.y] + 1;
                            // Verific daca din pozitia creata se
                            // poate iesi pe uscat si daca distanta pana
                            // la ea este mai mica decat min
                            // In acest caz actualizez min
                            if (Bord(xnou, ynou) == 1 && d[xnou][ynou] < min) {
                                min = d[xnou][ynou];
                            }
                            q.push({xnou, ynou});
                        }
                    }
                }
            }

            // Daca pe pozitia curenta este pod de tip O,
            // parcurg vectorul de deplari, creez coordonate noi.
            if (matrix[p.x][p.y] == 'O') {
                for (int i = 0; i < 2; i++) {
                    int ynou = p.y + podO[i];
                    // Verific daca coordonatele noi sunt in interiorul tablei
                    if (checkInside(p.x, ynou) == 1) {
                        // Actualizez distanta pana la pozitia xnou,ynou
                        // daca am gasit o solutie mai buna
                        if (d[p.x][p.y] + 1 < d[p.x][ynou]) {
                            d[p.x][ynou] = d[p.x][p.y] + 1;
                            // Verific daca din pozitia creata se
                            // poate iesi pe uscat si daca distanta pana
                            // la ea este mai mica decat min
                            // In acest caz actualizez min
                            if (Bord(p.x, ynou) == 1 && d[p.x][ynou] < min) {
                                min = d[p.x][ynou];
                            }
                            q.push({p.x, ynou});
                        }
                    }
                }
            }
            // Daca pe pozitia curenta este pod de tip V,
            // parcurg vectorul de deplari, creez coordonate noi.
            if (matrix[p.x][p.y] == 'V') {
                for (int i = 0; i < 2; i++) {
                    int xnou = p.x + podV[i];
                    // Verific daca coordonatele noi sunt in interiorul tablei
                    if (checkInside(xnou, p.y) == 1) {
                        // Actualizez distanta pana la pozitia xnou,ynou
                        // daca am gasit o solutie mai buna
                        if (d[p.x][p.y] + 1 < d[xnou][p.y]) {
                            d[xnou][p.y] = d[p.x][p.y] + 1;
                            // Verific daca din pozitia creata se
                            // poate iesi pe uscat si daca distanta pana
                            // la ea este mai mica decat min
                            // In acest caz actualizez min
                            if (Bord(xnou, p.y) == 1 && d[xnou][p.y] < min) {
                                min = d[xnou][p.y];
                            }
                            q.push({xnou, p.y});
                        }
                    }
                }
            }
        }
        if (min == INT_MAX) {
            return -1;
        }

        return min + 1;
    }

    int get_result() {
        return bfs(STARTX, STARTY);
    }

    // Scriere in fisierul de iesire
    void print_output(int result) {
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
