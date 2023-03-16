#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>

using namespace std;

void get_path(const std::vector<std::vector<int>>& spanning_tree, int s, int t, int n, std::vector<std::vector<int>>& edges) {
    map<int, std::vector<int>> graph;
    for (const auto &edge : spanning_tree) {
        int u = edge[0], v = edge[1];
        if (graph.find(u) == graph.end()) {
            graph[u] = std::vector<int>();
        }
        if (graph.find(v) == graph.end()) {
            graph[v] = std::vector<int>();
        }
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::function<bool(int, int, std::vector<std::vector<int>>&)> dfs = [&](int v, int parent, std::vector<std::vector<int>>& edges) {
        for (int u : graph[v]) {
            if (u == parent) continue;
            if (v>n) {
                edges.emplace_back(std::vector<int>{u, v});
            }
            else {
                edges.emplace_back(std::vector<int>{v, u});

            }
            if (u == t) return true;
            if (dfs(u, v, edges)) return true;
            edges.pop_back();
        }
        return false;
    };

    dfs(s, -1, edges);
    for (auto& edge : edges) {
        int& node1 = edge[0], &node2 = edge[1];
        if (node1 > n){
            node1 -= n;
        }
        else if (node2 > n){
            node2 -= n;
        }
    }
}


int degree_row(int u, const std::vector<std::vector<int>>& T) {
    int sum = 0;
    for (const auto& i : T) {
        if (i[0] == u) {
            sum += 1;
        }
    }
    return sum;
}


int degree_column(int v, const std::vector<std::vector<int>>& T) {
    int sum = 0;
    for (const auto& i : T) {
        if (i[1] == v) {
            sum += 1;
        }
    }
    return sum;
}


int signature(std::vector<std::vector<int>> &c) {
    // Initialization (dual feasible tree of level n-1)
    int n = c.size();
    std::vector<std::vector<int>> T;
    for (int j = 0; j < n; j++) {
        T.push_back({1, j+1});
    }

    std::vector<int> u, v, min_list;
    u.push_back(0);
    for (int j = 0; j < n; j++) {
        v.push_back(c[0][j]);
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            min_list.push_back(c[i][j] - v[j]);
        }
        u.push_back(*min_element(min_list.begin(), min_list.end()));
        T.push_back({i+1, (int)(min_element(min_list.begin(), min_list.end()) - min_list.begin()) + 1});
        min_list.clear();
    }
    int counter = 1;
    // k = level of T
    for (int k = n-1; k > 1; k--) {
        int s = -1;
        // Find the row with degree larger than 2
        for (int i = 0; i < T.size(); i++) {
            if (degree_row(T[i][0], T) > 2) {
                s = T[i][0];
                break;
            }
        }
        // If all rows have degree less than or equal to 2, break the loop
        if (s == -1) {
            break;
        }

        std::vector<int> T_one_degree;
        for (int i = 1; i <= n; i++) {
            if (i != s && degree_row(i, T) == 1) {
                T_one_degree.push_back(i);
            }
        }
        int t = T_one_degree[T_one_degree.size() - 1];

        while (degree_row(s, T) > 2) {
            counter++;
          // Define l
          std::vector<std::vector<int>> T_new;
          for (auto i : T) {
            T_new.push_back({i[0], i[1] + n});
          }

            std::vector<std::vector<int>> path_s_to_t;
            get_path(T_new, s, t, n, path_s_to_t);
            for (const auto& pair : path_s_to_t) {
                int first = pair[0];
                int second = pair[1];
                if (first > n) {
                    first -= n;
                }
                if (second > n) {
                    second -= n;
                }
            }


          auto l_edge = path_s_to_t[0];
          int l = path_s_to_t[0][1];

          // Remove [s, l] from T
          T.erase(std::remove(T.begin(), T.end(), l_edge), T.end());

          // Create the subtrees Ts and Tl
          std::vector<std::vector<int>> Ts, Tl;
          for (auto i : T) {
            if (i[0] == s) {
              Ts.push_back(i);
            }
          }
          for (auto i : T) {
            for (auto j : Ts) {
              if (std::find(Ts.begin(), Ts.end(), i) == Ts.end() && j[1] == i[1]) {
                Ts.push_back(i);
              }
            }
          }

          for (auto i : T) {
              if (i[1] == l) {
                Tl.push_back(i);
              }
            }

            for (auto i : T) {
              for (auto j : Tl) {
                if (std::find(Tl.begin(), Tl.end(), i) == Tl.end() && j[0] == i[0]) {
                  Tl.push_back(i);
                }
              }
            }

            for (auto i : T) {
              for (auto j : Tl) {
                if (std::find(Tl.begin(), Tl.end(), i) == Tl.end() && j[1] == i[1]) {
                  Tl.push_back(i);
                }
              }
            }

            std::vector<int> U_Tl;
            std::vector<int> V_Ts;
            std::vector<int> V_Tl;
            for (auto i : Tl) {
              if (std::find(U_Tl.begin(), U_Tl.end(),i[0]) == U_Tl.end()) {
                U_Tl.push_back(i[0]);
              }
            }

            for (auto i : Ts) {
              if (std::find(V_Ts.begin(), V_Ts.end(), i[1]) == V_Ts.end()) {
                V_Ts.push_back(i[1]);
              }
            }

            std::tuple<int, int> delta_index;
            int delta = 10000;
            for (auto i : U_Tl) {
              for (auto j : V_Ts) {
                int new_delta = c[i - 1][j - 1] - u[i - 1] - v[j - 1];
                if (new_delta < delta) {
                  delta = new_delta;
                  delta_index = std::make_tuple(i, j);
                }
              }
            }

            std::vector<int> inner_vector{std::get<0>(delta_index), std::get<1>(delta_index)};
            T.push_back(inner_vector);

            for (auto i : Tl) {
                if (find(V_Tl.begin(), V_Tl.end(), i[1]) == V_Tl.end()) {
                    V_Tl.push_back(i[1]);
                }
            }

            for (auto i : U_Tl) {
                u[i-1] += delta;
            }

            for (auto i : V_Tl) {
                v[i-1] -= delta;
            }

            s = l_edge[0];

        }

    }
    // out of for

    int r = 0;
    for (int i = 0; i <= n; i++) {
        if (degree_row(i, T) == 1) {
            r = i;
        }
    }

    std::vector<std::vector<int>> T_new;
    for (auto i : T) {
        T_new.push_back({i[0], i[1] + n});
    }

    std::vector<int> row_one_degree;
    std::vector<int> column_one_degree;
    for (auto i : T) {
        if (degree_row(i[0], T) == 1) {
            row_one_degree.push_back(i[0]);
        }
        if (degree_column(i[1], T) == 1) {
            column_one_degree.push_back(i[1] + n);
        }
    }

    std::vector<std::vector<std::vector<int>>> path;
    std::vector<std::vector<int>> odd_edges;
    std::vector<std::vector<int>> even_edges;
    for (auto i : column_one_degree) {
        std::vector<std::vector<int>> edges;
        get_path(T_new, r, i, n, edges);
        path.push_back(edges);
    }
    for (auto i : path) {
        for (int j = 0; j < i.size(); j++) {
            if (j % 2 == 0) {
                if (find(odd_edges.begin(), odd_edges.end(), i[j]) == odd_edges.end()) {
                    odd_edges.push_back(i[j]);
                }
            } else {
                std::vector<int> edge = {i[j][1], i[j][0]};
                if (find(even_edges.begin(), even_edges.end(), edge) == even_edges.end()) {
                    even_edges.push_back(edge);
                }
            }
        }
    }

    std::vector<std::vector<int>> x(n, std::vector<int>(n, 0));
    for (auto i : odd_edges) {
        x[i[0] - 1][i[1] - 1] = 1;
    }
    std::cout << "# minimal cost: " << counter << std::endl;
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[0].size(); j++) {
            if (x[i][j] == 1) {
                std::cout << i + 1 <<" " << j+1 << std::endl;
            }
        }
    }

    return 0;

}

int main(){
    int n, m;
    std::cout << "Enter the number of workers and jobs: ";
    std::cin >> n >> m;
    std::vector<std::vector<int>> c(n, std::vector<int>(n, 0));

    std::cout << "Enter the cost matrix: ";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> c[i][j];
        }
    }

    signature(c);
    return 0;
}
