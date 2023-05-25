#include <iostream>
#include <queue>
#include <limits>
#include <vector>
#include <algorithm>
#include <unordered_set>

class Graph {
 private:
  std::vector<std::unordered_set<int>> vertexes_;
  std::vector<int> dist_;
  std::vector<int> parents_;

 public:
  explicit Graph(int n) {
    vertexes_ = std::vector<std::unordered_set<int>>(n);
    dist_ = std::vector<int>(n, std::numeric_limits<int>::max());
    parents_ = std::vector<int>(n, -1);
  }

  void BFS(int start) {
    std::queue<int> queue;
    queue.push(start);
    dist_[start] = 0;

    while (!queue.empty()) {
      int curr = queue.front();
      queue.pop();

      for (auto neighbour : vertexes_[curr]) {
        if (dist_[neighbour] > dist_[curr] + 1) {
          dist_[neighbour] = dist_[curr] + 1;
          parents_[neighbour] = curr;
          queue.push(neighbour);
        }
      }
    }
  }

  friend std::istream& operator>>(std::istream& is, Graph& g);

  std::vector<int> ShortestPath(int end) {
    int x = end;
    std::vector<int> shortest_path;
    while (parents_[x] != -1) {
      shortest_path.push_back(x);
      x = parents_[x];
    }

    shortest_path.push_back(x);
    std::reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
  }

  void SetVertex(int begin, int end) {
    vertexes_[begin].insert(end);
    vertexes_[end].insert(begin);
  }

  int GetDist(int i) {
    return dist_[i];
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;

  g.SetVertex(begin, end);
  return is;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  int begin, end;
  std::cin >> begin >> end;

  Graph g(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }
  g.BFS(--begin);

  if (g.GetDist(--end) == std::numeric_limits<int>::max()) {
    std::cout << -1;
  } else {
    std::cout << g.GetDist(end) << '\n';

    std::vector<int> ans = g.ShortestPath(end);
    for (size_t i = 0; i < ans.size(); ++i) {
      std::cout << ans[i] + 1 << ' ';
    }
  }
}
