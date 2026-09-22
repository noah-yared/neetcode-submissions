class Solution {
public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
        vector<pair<int, int>> indexed_heights;
        for (int i = 0; i < names.size(); ++i) {
            indexed_heights.emplace_back(i, heights[i]);
        }

        sort(indexed_heights.begin(), indexed_heights.end(), [](auto a, auto b){ return a.second < b.second; });

        vector<string> sorted;
        for (int i = names.size() - 1; i >= 0; --i) {
            sorted.push_back(names[indexed_heights[i].first]); 
        }
        return sorted;
    }
};