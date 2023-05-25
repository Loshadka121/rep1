#include <iostream>
#include <vector>

class CDS {
 private:
  std::vector<int> parents_;
  std::vector<int> rank_;

 public:
  explicit CDS(size_t n) {
    rank_ = std::vector<int>(n, 0);
    parents_ = std::vector<int>(n);
    for (size_t i = 0; i < n; ++i) {
      parents_[i] = i;
    }
  };

  int FindSet(int x) {
    if (x == parents_[x]) {
      return x;
    }

    return parents_[x] = FindSet(parents_[x]);
  }

  void Union(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);

    if (rank_[x] < rank_[y]) {
      parents_[x] = y;
    } else if (rank_[x] > rank_[y]) {
      parents_[y] = x;
    } else {
      parents_[x] = y;
      ++rank_[y];
    }
  }
};

struct Edge {
  int weight_;
  int first_;
  int second_;

  bool operator<(const Edge& other) const {
    return weight_ < other.weight_;
  }
};

struct Graph {
  std::vector<Edge> edges_;
  std::vector<Edge> MST_;
  int n_;
  int tree_weight_ = 0;

  explicit Graph(int m) : n_(m) {
    edges_ = std::vector<Edge>(m);
    MST_ = std::vector<Edge>(m);
  }
};

void FindMST(Graph& graph) {
  CDS cds(graph.n_);
  for (auto edge : graph.edges_) {
    if (cds.FindSet(edge.first_) != cds.FindSet(edge.second_)) {
      cds.Union(edge.first_, edge.second_);
      graph.MST_.push_back(edge);
      graph.tree_weight_ += edge.weight_;
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  Graph graph(m);

  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;

    graph.edges_[i].first_ = u;
    graph.edges_[i].second_ = v;
    graph.edges_[i].weight_ = w;
  }

  FindMST(graph);
  std::cout << graph.tree_weight_;

  return 0;
}
