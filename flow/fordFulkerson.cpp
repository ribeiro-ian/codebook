// Ford-Fulkerson (BFS = Edmonds-Karp)
// Retorna o fluxo maximo entre s e t
// O(V * E^2)

const ll INF = 1e18;
vector<vector<ll>> cap;
vector<vector<ll>> adj;
int n, m;

ll bfs(int s, int t, vector<ll>& pai) {
  fill(pai.begin(), pai.end(), -1);
  pai[s] = -2;
  queue<pair<ll, ll>> q;
  q.push({s, INF});

  while (!q.empty()) {
    auto [u, fluxo] = q.front();
    q.pop();

    for (auto& v : adj[u]) {
      if (pai[v] == -1 && cap[u][v] > 0) {
        pai[v] = u;
        ll novo_fluxo = min(fluxo, cap[u][v]);
        if (v == t) return novo_fluxo;
        q.push({v, novo_fluxo});
      }
    }
  }

  return 0;
}

ll ford_fulkerson(int s, int t) {
  ll fluxo = 0;
  vector<ll> pai(n + 1);
  ll novo_fluxo;

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
adj.assign(n+1, {});
cap.assign(n+1, vector<ll>(n+1));
// para cada aresta a-b com peso c:
// adj[a].push_back(b); adj[b].push_back(a); cap[a][b] += c;