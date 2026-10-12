#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class UnionFind {
private:
    map<long long, long long> parent;
    map<long long, long long> rank;
    
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
            constraints.push_back({{x, y}, e});
        }
        
        UnionFind uf;
        
        // Process equality constraints first
        for (const auto& constraint : constraints) {
            long long x = constraint.first.first;
            long long y = constraint.first.second;
            int e = constraint.second;
            
            if (e == 1) {
                uf.unite(x, y);
            }
        }
        
        bool possible = true;
        
        // Check inequality constraints
        for (const auto& constraint : constraints) {
            long long x = constraint.first.first;
            long long y = constraint.first.second;
            int e = constraint.second;
            
            if (e == 0) {
                if (uf.connected(x, y)) {
                    possible = false;
                    break;
                }
            }
        }
        
        cout << (possible ? "YES" : "NO") << "\n";
    }
    
    return 0;
}