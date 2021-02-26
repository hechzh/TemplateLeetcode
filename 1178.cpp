struct TrieNode {
    int frequency = 0;
    TrieNode* child[26];

    TrieNode() {
        for (int i = 0; i < 26; ++i) {
            child[i] = nullptr;
        }
    }
};

class Solution {
private:
    TrieNode* root;

public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        root = new TrieNode();

        auto add = [&](const string& word) {
            TrieNode* cur = root;
            for (char ch: word) {
                if (!cur->child[ch - 'a']) {
                    cur->child[ch - 'a'] = new TrieNode();
                }
                cur = cur->child[ch - 'a'];
            }
            ++cur->frequency;
        };

        // 在回溯的过程中枚举 puzzle 的所有子集并统计答案
        // find(puzzle, required, cur, pos) 表示 puzzle 的首字母为 required, 当前搜索到字典树上的 cur 节点，并且准备枚举 puzzle 的第 pos 个字母是否选择（放入子集中）
        // find 函数的返回值即为谜底的数量
        function<int(const string&, char, TrieNode*, int)> find = [&](const string& puzzle, char required, TrieNode* cur, int pos) {
            // 搜索到空节点，不合法，返回 0
            if (!cur) {
                return 0;
            }
            // 整个 puzzle 搜索完毕，返回谜底的数量
            if (pos == 7) {
                return cur->frequency;
            }
            
            // 选择第 pos 个字母
            int ret = find(puzzle, required, cur->child[puzzle[pos] - 'a'], pos + 1);

            // 当 puzzle[pos] 不为首字母时，可以不选择第 pos 个字母
            if (puzzle[pos] != required) {
                ret += find(puzzle, required, cur, pos + 1);
            }
            
            return ret;
        };
        
        for (string word: words) {
            // 将 word 中的字母按照字典序排序并去重
            sort(word.begin(), word.end());
            word.erase(unique(word.begin(), word.end()), word.end());
            // 加入字典树中
            add(word);
        }

        vector<int> ans;
        for (string puzzle: puzzles) {
            char required = puzzle[0];
            sort(puzzle.begin(), puzzle.end());
            ans.push_back(find(puzzle, required, root, 0));
        }
        return ans;
    }
};
