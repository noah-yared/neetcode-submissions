class Solution {
    bool adjacent(const std::string& s1, const std::string& s2) {
        int diffs = 0;
        for (int i = 0; i < s1.size(); ++i) {
            if (s1[i] != s2[i]) ++diffs;
            if (diffs > 1) {
                return false;
            }
        }
        return diffs == 1;
    }

    int bfs(vector<vector<int>>& graph, vector<bool>& vis, int cur, int target) {
        int transformations = 1;
        vector<int> q, new_q;
        q.push_back(cur);
        while (!q.empty() || !new_q.empty()) {
            if (q.empty()) {
                q = std::move(new_q);
                ++transformations;
            }
            int n = q.front(); q.erase(q.begin());
            if (n == target) {
                return transformations;
            }
            vis[n] = true;
            for (int nr : graph[n]) {
                if (vis[nr]) {
                    continue;
                }
                new_q.push_back(nr);
            }
        }
        return 0;
    } 
    
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if (auto it = std::find(wordList.begin(), wordList.end(), beginWord); it == wordList.end()) {
            wordList.push_back(beginWord);
        }
        if (auto it = std::find(wordList.begin(), wordList.end(), endWord); it == wordList.end()) {
            return 0;
        }
        vector<vector<int>> adj_graph(wordList.size());
        for (int i = 0; i < wordList.size(); ++i) {
            for (int j = i + 1; j < wordList.size(); ++j) {
                if (adjacent(wordList[i], wordList[j])) {
                    adj_graph[i].push_back(j);
                    adj_graph[j].push_back(i);
                }
            }
        }

        vector<bool> vis(wordList.size(), false);

        int start = std::find(wordList.begin(), wordList.end(), beginWord) - wordList.begin();
        int end = std::find(wordList.begin(), wordList.end(), endWord) - wordList.begin();

        return bfs(adj_graph, vis, start, end);
    }
};
