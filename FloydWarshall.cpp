#include <iostream>
#include <vector>

class Graph {
 private:
  size_t v_;
  std::vector<std::vector<int>> vertex_matrix_;
  std::vector<std::vector<int>> ways_matrix_;

 public:
  explicit Graph(int n) {
    v_ = n;
    vertex_matrix_.resize(v_, std::vector<int>(v_));
  }

  void FloydWarshall() {
    ways_matrix_ = vertex_matrix_;
    for (size_t k = 0; k < v_; ++k) {
      for (size_t x = 0; x < v_; ++x) {
        for (size_t y = 0; y < v_; ++y) {
          ways_matrix_[x][y] = std::min(ways_matrix_[x][y], ways_matrix_[x][k] + ways_matrix_[k][y]);
        }
      }
    }
  }

  void GraphIn() {
    for (size_t i = 0; i < v_; ++i) {
      for (size_t j = 0; j < v_; ++j) {
        std::cin >> vertex_matrix_[i][j];
      }
    }
  }
  void WaysOut() {
    for (size_t x = 0; x < v_; ++x) {
      for (size_t y = 0; y < v_; ++y) {
        std::cout << ways_matrix_[x][y] << " ";
      }
      std::cout << '\n';
    }
  }
};

int main() {
  int n;
  std::cin >> n;
  Graph g(n);

  g.GraphIn();
  g.FloydWarshall();
  g.WaysOut();

  return 0;
}
