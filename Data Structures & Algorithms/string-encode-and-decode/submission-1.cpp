class Solution {
public:
    // Encoding scheme: We separate strings with a ',' and start strings with 'x'
    // to distinguish empty set of encoded strings represented as "".
    // To use a ',' normally, it must be "escaped" with a bang '!'.
    // To use a '!' normally in front of a ',', we must place another
    // bang '!' before it. For example:
    // "!!," => "!" + "" || ".!,e" => ".,e" || ".,e" => "." + "e"
    string encode(vector<string>& strs) {
        if (strs.empty()) {
            return "";
        }
        // Dummy start char is 'x'
        vector<char> chars{'x'};
        for (int sid = 0; sid < strs.size(); ++sid) {
            const auto& s = strs[sid];
            for (auto it = s.begin(); it != s.end(); ++it) {
                auto it_old = it;
                // Find first iterator at or after it such that *it != '!'
                // Add '!' as we iterate.
                while (*it == '!' && ++it != s.end()) {
                    chars.push_back('!');
                }
                if ((it == s.end() && (sid != strs.size() - 1)) || *it == ',') {
                    for (int i = 0; i < it - it_old; ++i) {
                        // Need to escape the previous bangs '!', they are
                        // followed by ','.
                        chars.push_back('!');
                    }
                    if (it == s.end()) {
                        // Reached end of string.
                        break;
                    }
                    // Add additional '!' to escape ','
                    chars.push_back('!');
                } else {
                // No need to escape '!'s since '!'s not followed by a comma.
                }
                chars.push_back(*it);
            }
            // Separator
            if (sid != strs.size() - 1) {
                chars.push_back(',');
            }
        }
        return {chars.begin(), chars.end()};
    }

    vector<string> decode(string s) {
        if (s.empty()) {
            return {};
        }
        vector<string> strs;
        vector<char> str;
        for (auto it = s.begin() + 1; it != s.end(); ++it) {
            auto it_old = it;
            while (*it == '!' && ++it != s.end()) ;
            if (it == s.end() || *it != ',') {
                for (int i = 0; i < it - it_old; ++i) {
                    str.push_back('!');
                }
                if (it == s.end())
                    break;
                str.push_back(*it);
            } else {
                int num_bangs = (it - it_old) / 2;
                for (int i = 0; i < num_bangs; ++i) {
                    str.push_back('!');
                }
                bool sep_escaped = (it - it_old) & 1;
                if (sep_escaped) {
                    str.push_back(',');
                } else {
                    // Unescaped comma implies string separator
                    strs.push_back({str.begin(), str.end()});
                    str.clear();
                }
            }
        }
        // Push last string (we only push above when we hit separator)
        strs.push_back({str.begin(), str.end()});
        return strs;
    }
};
