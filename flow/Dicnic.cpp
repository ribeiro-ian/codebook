// O(V^2 * E) geral, O(E * sqrt(V)) para matching bipartido
struct Dinic {
  struct Edge {
    int to, rev;
    int cap, flow;
  };

  int n;
  vector<vector<Edge>> g;
  vector<int> level, ptr;

  Dinic(int n) : n(n), g(n), level(n), ptr(n) {}

  void add_edge(int u, int v, int cap) {
    g[u].push_back({v, (int)g[v].size(), cap, 0});
    g[v].push_back({u, (int)g[u].size() - 1, 0, 0});
  }

  bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    queue<int> q;
    level[s] = 0;
    q.push(s);

    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (auto &e : g[u]) {
        if (level[e.to] == -1 && e.flow < e.cap) {
          level[e.to] = level[u] + 1;
          q.push(e.to);
        }
      }
    }
    return level[t] != -1;
  }

  int dfs(int u, int t, int f) {
    if (u == t || f == 0) return f;

    for (int &i = ptr[u]; i < g[u].size(); i++) {
      Edge &e = g[u][i];
      if (level[e.to] == level[u] + 1) {
        int pushed = dfs(e.to, t, min(f, e.cap - e.flow));
        if (pushed > 0) {
          e.flow += pushed;
          g[e.to][e.rev].flow -= pushed;
          return pushed;
        }
      }
    }
    return 0;
  }

  int max_flow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
      fill(ptr.begin(), ptr.end(), 0);
      while (int pushed = dfs(s, t, 1e18))
        flow += pushed;
    }
    return flow;
  }

  // Arestas do corte mínimo: visitáveis de s no grafo residual
  vector<pair<int, int>> min_cut(int s) {
    vector<bool> vis(n);
    queue<int> q;
    q.push(s); vis[s] = true;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (auto &e : g[u])
        if (!vis[e.to] && e.flow < e.cap) {
          vis[e.to] = true;
          q.push(e.to);
        }
    }
    vector<pair<int, int>> cut;
    for (int u = 0; u < n; u++)
      if (vis[u])
        for (auto &e : g[u])
          if (!vis[e.to] && e.cap > 0)
            cut.push_back({u, e.to});
    return cut;
  }
};
