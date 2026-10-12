#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        vector<pair<long long, long long>> equal_constraints;
        vector<pair<long long, long long>> unequal_constraints;
        equal_constraints.reserve(n);
        unequal_constraints.reserve(n);
        
        vector<long long> all_values;
        all_values.reserve(n * 2);
        
        for (int i = 0; i < n; i++) {
            long long x, y;
            int e;
            scanf("%lld %lld %d", &x, &y, &e);
            all_values.push_back(x);
            all_values.push_back(y);
            if (e == 1) {
                equal_constraints.emplace_back(x, y);
            } else {
                unequal_constraints.emplace_back(x, y);
            }
        }
        
        // Coordinate compression
        sort(all_values.begin(), all_values.end());
        all_values.erase(unique(all_values.begin(), all_values.end()), all_values.end());
        
        unordered_map<long long, int> coord_map;
        coord_map.reserve(all_values.size() * 2);
        for (int i = 0; i < (int)all_values.size(); i++) {
            coord_map[all_values[i]] = i;
        }
        
        UnionFind uf(all_values.size());
        
        // Process equality constraints
        for (const auto& constraint : equal_constraints) {
            int x_idx = coord_map[constraint.first];
            int y_idx = coord_map[constraint.second];
            uf.unite(x_idx, y_idx);
        }
        
        bool possible = true;
        
        // Check inequality constraints
        for (const auto& constraint : unequal_constraints) {
            int x_idx = coord_map[constraint.first];
            int y_idx = coord_map[constraint.second];
            if (uf.connected(x_idx, y_idx)) {
                possible = false;
                break;
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}