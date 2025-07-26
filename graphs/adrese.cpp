#include <bits/stdc++.h>
#include <iostream>
using namespace std;

ifstream fin("adrese.in");
ofstream fout("adrese.out");

// Structura pentru a defini o componenta conexa
struct compcon {
    // Perecehe formata dintr-un set de mail-uri si numele persoanei
    pair<std::set<std::string, less_equal<std::string>>, string> cc;
    // Numarul de mailuri
    int dim;

    // Comparator
    // Daca au aceeasi dimensiune ordonez crescator dupa nume,
    // altfel dupa dimensiune
    bool operator<(const compcon &p) const {
        if (dim == p.dim) {
            return cc.second < p.cc.second;
        } else {
            return dim < p.dim;
        }
    }
};

class Task {
 public:
    void solve() {
        read_input();
        get_result();
    }

 private:
    int n;
    int V = 1;

    // Liste de adiacenta
    // Nodurile sunt reprezentate de mail-uri
    vector<int> adj[500005];

    // Map ce face corespondenta intre un mail si un id
    unordered_map<string, int> mails;

    // Map ce face corespondenta intre un id si un mail
    unordered_map<int, string> mailstr;

    // Map ce face  corespondenta intre un mail si un nume
    unordered_map<string, string> p;

    list<compcon> ccs;

    // Citire fisier de intrare
    void read_input() {
        fin >> n;
        for (int i = 1; i <= n; i++) {
            string nume;
            fin >> nume;
            int nr;
            fin >> nr;
            int k = 0;
            for (int j = 1; j <= nr; j++) {
                string s;
                fin >> s;

                // S-a citit primul mail al unei persoane
                if (k == 0) {
                    // Caut mail-ul citit in map de mailuri
                    unordered_map<string, int>::iterator it = mails.find(s);
                    // Daca nu a fost gasit il adaug in mapul mails,mailstr
                    // si in mapul de parinti p
                    if (it == mails.end()) {
                        mails.insert({s, V});
                        mailstr.insert({V, s});
                        p.insert({s, nume});
                        k = V;
                        V++;
                    } else {
                        // Mail-ul a fost gasit
                        // Atunci fac legatura intre el si nodul curent
                        adj[V].push_back(it->second);
                        adj[it->second].push_back(V);
                    }
                } else {
                    // Caut mail-ul citit in lista de mailuri
                    unordered_map<string, int>::iterator iter = mails.find(s);
                    // Daca nu a fost gasit il adaug in mapul mails,mailstr
                    // mapul de parinti p si faca legatura intre el si nodul
                    // precedent
                    if (iter == mails.end()) {
                        mails.insert({s, V});
                        mailstr.insert({V, s});
                        adj[k].push_back(V);
                        adj[V].push_back(k);
                        p.insert({s, nume});
                        k = V;
                        V++;
                    } else {
                        // Mail-ul a fost gasit
                        // Atunci fac legatura intre el si nodul curent
                        adj[k].push_back(iter->second);
                        adj[iter->second].push_back(k);
                    }
                }
            }
        }
        V--;
        fin.close();
    }

    vector<pair<std::set<std::string, less_equal<std::string>>, string>> cc() {
        vector<bool> used(V + 1, false);
        // STEP 2: visit all nodes
        vector<pair<std::set<std::string,
        less_equal<std::string>>, string>> all_ccs;
        for (int node = 1; node <= V; ++node) {
            if (!used[node]) {
                // STEP 3: start a new DFS traversal this subtree
                pair<std::set<std::string, less_equal<std::string>>, string> cc;
                cc.second = "";
                dfsiter(node, used, cc);
                all_ccs.push_back(cc);
            }
        }
        return all_ccs;
    }

    // DFS recursiv
    void dfs(int node, vector<bool> &used,
             pair<std::set<std::string,
             less_equal<std::string>>, string> &cc) {
        used[node] = true;
        unordered_map<int, string>::iterator iter = mailstr.find(node);
        cc.first.insert(iter->second);
        for (auto &neigh : adj[node]) {
            if (!used[neigh]) {
                dfs(neigh, used, cc);
            }
        }
        unordered_map<string, string>::iterator it = p.find(iter->second);

        if (cc.second == "") {
            cc.second = it->second;
        } else {
            if (it->second.compare(cc.second) < 0) {
                cc.second = it->second;
            }
        }
    }

    // DFS iterativ
    // Intoarce componenta conexa gasita in parcurgerea dfs
    // din nodul dat ca prametru
    void dfsiter(int node, vector<bool> &used,
            pair<std::set<std::string, less_equal<std::string>>, string> &cc) {
        stack<int> stack;

        stack.push(node);

        while (!stack.empty()) {
            // Extrag nodul din stiva
            node = stack.top();
            stack.pop();

            // Daca nodul nu a fost vizitat,
            // adaug mail-ul corepunzator id-ului
            // in componenta conexa
            // Si setez numele persoanei componentei conexe
            // (numele persoanei ce are mail-urile curente)
            // la cel mai mic nume dpdv lexicografic

            if (!used[node]) {
                used[node] = true;
                unordered_map<int, string>::iterator iter = mailstr.find(node);
                cc.first.insert(iter->second);
                unordered_map<string, string>::iterator it;
                it = p.find(iter->second);
                if (cc.second == "") {
                    cc.second = it->second;
                } else {
                    if (it->second.compare(cc.second) < 0) {
                        cc.second = it->second;
                    }
                }
            }

            // Parcurg veciinii nodului curent
            for (auto &neigh : adj[node]) {
                if (!used[neigh]) {
                    stack.push(neigh);
                }
            }
        }
    }

    void get_result() {
        vector<pair<std::set<std::string, less_equal<std::string>>,
        string>> all_ccs = cc();
        list<compcon> l;
        fout << all_ccs.size() << '\n';
        // Parcurg vectorul de componente conexe
        // si adaug elementele intr-o lista
        // pe care o sortez
        for (const auto &cc : all_ccs) {
            compcon p;
            p.cc = cc;
            p.dim = cc.first.size();
            l.push_front(p);
        }
        l.sort();

        // Afisare componente conexe
        for (auto a : l) {
            fout << a.cc.second << " " << a.cc.first.size() << " \n";
            for (auto node : a.cc.first) {
                fout << node << "\n";
            }
        }
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
