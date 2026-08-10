// Segment Tree nas linhas, outra dinâmica nas colunas
// O(log^2 N) por operação, O(Q log^2 N) espaço
//
// Quando usar:
// - Grid N x N com N grande (até 1e9) e poucas operações
// - Queries do tipo: soma em retângulo (x1,y1)-(x2,y2)
//
// Uso:
//   SegTree2D st(N); // N = limite das coordenadas
//   st.update(x, y, val);
//   st.query(x1, y1, x2, y2);

struct SegTree2D {
  struct NodeY {
    int val;
    NodeY *left, *right;
    NodeY() : val(0), left(nullptr), right(nullptr) {}
  };

  struct NodeX {
    NodeY* yRoot;
    NodeX *left, *right;
    NodeX() : yRoot(new NodeY()), left(nullptr), right(nullptr) {}
  };

  NodeX* root;
  int N;

  SegTree2D(int N) : N(N), root(new NodeX()) {}

  // Atualiza coluna y com delta na árvore Y do nó X
  void updateY(NodeY* no, int l, int r, int y, int delta) {
    if (l == r) {
      no->val += delta;
      return;
    }
    int m = l + (r - l) / 2;
    if (y <= m) {
      if (!no->left) no->left = new NodeY();
      updateY(no->left, l, m, y, delta);
    }
    else {
      if (!no->right) no->right = new NodeY();
      updateY(no->right, m + 1, r, y, delta);
    }
    no->val = (no->left  ? no->left->val : 0) + (no->right ? no->right->val : 0);
  }

  int queryY(NodeY* no, int l, int r, int ql, int qr) {
    if (!no || l > qr || r < ql) return 0;
    if (l >= ql && r <= qr) return no->val;
    int m = l + (r - l) / 2;
    return queryY(no->left,  l,   m, ql, qr)
           + queryY(no->right, m + 1, r, ql, qr);
  }

  // Desce na árvore X atualizando a árvore Y de cada nó afetado
  void updateX(NodeX* no, int l, int r, int x, int y, int delta) {
    updateY(no->yRoot, 1, N, y, delta); // atualiza este nó X
    if (l == r) return;
    int m = l + (r - l) / 2;
    if (x <= m) {
      if (!no->left) no->left = new NodeX();
      updateX(no->left, l, m, x, y, delta);
    }
    else {
      if (!no->right) no->right = new NodeX();
      updateX(no->right, m + 1, r, x, y, delta);
    }
  }

  int queryX(NodeX* no, int l, int r, int xl, int xr, int yl, int yr) {
    if (!no || l > xr || r < xl) return 0;
    if (l >= xl && r <= xr) return queryY(no->yRoot, 1, N, yl, yr);
    int m = l + (r - l) / 2;
    return queryX(no->left,  l, m, xl, xr, yl, yr) + queryX(no->right, m + 1, r, xl, xr, yl, yr);
  }

  // Adiciona delta em (x, y)
  void update(int x, int y, int delta) {
    updateX(root, 1, N, x, y, delta);
  }

  // Soma em retângulo (x1,y1)-(x2,y2)
  int query(int x1, int y1, int x2, int y2) {
    return queryX(root, 1, N, x1, x2, y1, y2);
  }
};
