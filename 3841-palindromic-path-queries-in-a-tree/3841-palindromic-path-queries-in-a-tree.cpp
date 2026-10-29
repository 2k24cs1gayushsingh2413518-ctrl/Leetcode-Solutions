#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Solution {
    int n, timer;
    vector<vector<int>> adj;
    vector<int> tin, tout;
    vector<vector<int>> up;
    vector<int> bit; // Fenwick Tree for Range XOR updates and Point Queries
    int LOG;

    // Fenwick Tree operations
    void updateBIT(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] ^= val;
        }
    }

    void rangeUpdate(int l, int r, int val) {
        updateBIT(l, val);
        updateBIT(r + 1, val);
    }

    int queryBIT(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum ^= bit[idx];
        }
        return sum;
    }

    // DFS to establish Euler Tour and Binary Lifting table
    void dfs(int u, int p) {
        tin[u] = ++timer;
        up[u][0] = p; // Corrected: up[u] is a vector, we must access index 0
        for (int i = 1; i < LOG; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1]; // Corrected matrix lookup
        }

        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
        tout[u] = timer;
    }

    // Standard LCA check using Binary Lifting
    bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int getLCA(int u, int v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int i = LOG - 1; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v)) {
                u = up[u][i];
            }
        }
        return up[u][0]; // Corrected: returning parent of u
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        this->n = n;
        timer = 0;
        LOG = 0;
        while ((1 << LOG) <= n) LOG++;
        
        adj.assign(n, vector<int>());
        tin.resize(n);
        tout.resize(n);
        up.assign(n, vector<int>(LOG));
        bit.assign(n + 2, 0);

        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Initialize tree structure with node 0 as root
        dfs(0, 0);

        // Track active character configurations at each node
        vector<char> current_char(n);
        for (int i = 0; i < n; ++i) {
            current_char[i] = s[i];
            int mask = 1 << (s[i] - 'a');
            rangeUpdate(tin[i], tout[i], mask);
        }

        vector<bool> result;

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            ss >> type;

            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;

                int old_mask = 1 << (current_char[u] - 'a');
                int new_mask = 1 << (c - 'a');
                
                // Remove old character mask and apply new character mask to subtree
                rangeUpdate(tin[u], tout[u], old_mask ^ new_mask);
                current_char[u] = c;
            } else {
                int u, v;
                ss >> u >> v;

                int lca = getLCA(u, v);
                
                // Path XOR: root-to-u XOR root-to-v
                int path_mask = queryBIT(tin[u]) ^ queryBIT(tin[v]);
                
                // Add back the LCA's own character parity
                path_mask ^= (1 << (current_char[lca] - 'a'));

                // Verify if at most one bit remains set
                bool can_form_palindrome = (path_mask & (path_mask - 1)) == 0;
                result.push_back(can_form_palindrome);
            }
        }

        return result;
    }
};
