#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class UnionFind {
private:
    unordered_map<long long, long long> parent;
    unordered_map<long long, long long> rank;
    
public:
    long long find(long long x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(long long x, long long y) {
        long long rootX = find(x);
        long long rootY = find(y);
        
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
    
    bool connected(long long x, long long y) {
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
        
        for (int i = 0; i < n; i++) {
            long long x, y;
            int e;
            cin >> x >> y >> e;
            constraints.emplace_back(make_pair(x, y), e);
        }
        
        UnionFind uf;
        
        // Process equality constraints first
        for (const auto& constraint : constraints) {
            if (constraint.second == 1) {
                uf.unite(constraint.first.first, constraint.first.second);
            }
        }
        
        bool possible = true;
        
        // Check inequality constraints
        for (const auto& constraint : constraints) {
            if (constraint.second == 0) {
                if (uf.connected(constraint.first.first, constraint.first.second)) {
                    possible = false;
                    break;
                }
            }
        }
        
        cout << (possible ? "YES" : "NO") << "\n";
    }
    
    return 0;
}