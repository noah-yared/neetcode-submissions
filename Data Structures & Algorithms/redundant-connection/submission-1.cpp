class Solution {
    class DSU {
      public:
        DSU(int n) : parent(n + 1), rank(n + 1) {
            iota(parent.begin(), parent.end(), 0);
        }

        bool unite(int a, int b) {
            a = find(a), b = find(b);

            if (a == b) {
                return false;
            }

            if (rank[a] < rank[b]) {
                swap(a, b);
            }

            rank[a] = std::max(rank[a], rank[b] + 1);
            parent[b] = a;
            return true;
        }

        int find(int a) {
            while (parent[a] != parent[parent[a]]) {
                // Path compression; we move parent of a up every
                // iteration so we eventually reach the root.
                parent[a] = parent[parent[a]];
            }
            return parent[a];
        }

      private:
        vector<int> parent;
        vector<int> rank;
    };

public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        DSU dsu(edges.size());
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            if (!dsu.unite(u, v)) {
                return {u, v};
            }
        }
        return {};
    }
};
