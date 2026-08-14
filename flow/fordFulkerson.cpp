// Ford-Fulkerson (BFS = Edmonds-Karp)
// Retorna o fluxo maximo entre s e t
// O(V * E^2)

const int INF = 1e18;
vector<vector<int>> cap;
vector<vector<int>> adj;
int n, m;

int bfs(int s, int t, vector<int>& pai) {
    fill(pai.begin(), pai.end(), -1);
    pai[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        auto [u, fluxo] = q.front();
        q.pop();

        for (auto& v : adj[u]) {
            if (pai[v] == -1 && cap[u][v] > 0) {
                pai[v] = u;
                int novo_fluxo = min(fluxo, cap[u][v]);
                if (v == t) return novo_fluxo;
                q.push({v, novo_fluxo});
            }
        }
    }

    return 0;
}

int ford_fulkerson(int s, int t) {
    int fluxo = 0;
    vector<int> pai(n + 1);
    int novo_fluxo;

    while (novo_fluxo = bfs(s, t, pai)) {
        fluxo += novo_fluxo;
        int u = t;
        while (u != s) {
            int p = pai[u];
            cap[p][u] -= novo_fluxo;
            cap[u][p] += novo_fluxo;
            u = p;
        }
    }

    return fluxo;
}
// no main:
adj.assign(n + 1, {});
cap.assign(n + 1, vector<int>(n + 1));
// para cada aresta a-b com peso c:
// adj[a].push_back(b); adj[b].push_back(a); cap[a][b] += c;
