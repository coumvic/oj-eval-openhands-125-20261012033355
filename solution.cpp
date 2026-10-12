#include <iostream>
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<pair<pair<long long, long long>, int>> constraints;
        constraints.reserve(n);
        
        vector<long long> all_values;
        all_values.reserve(n * 2);
        
        for (int i = 0; i < n; i++) {
            long long x, y;
            int e;
            cin >> x >> y >> e;
            constraints.emplace_back(make_pair(x, y), e);
            all_values.push_back(x);
            all_values.push_back(y);
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
        
        // Process equality constraints first
        for (const auto& constraint : constraints) {
            if (constraint.second == 1) {
                int x_idx = coord_map[constraint.first.first];
                int y_idx = coord_map[constraint.first.second];
                uf.unite(x_idx, y_idx);
            }
        }
        
        bool possible = true;
        
        // Check inequality constraints
        for (const auto& constraint : constraints) {
            if (constraint.second == 0) {
                int x_idx = coord_map[constraint.first.first];
                int y_idx = coord_map[constraint.first.second];
                if (uf.connected(x_idx, y_idx)) {
                    possible = false;
                    break;
                }
            }
        }
        
        cout << (possible ? "YES" : "NO") << "\n";
    }
    
    return 0;
}