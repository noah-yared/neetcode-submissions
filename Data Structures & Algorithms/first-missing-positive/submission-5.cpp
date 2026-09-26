class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        // Note that the first missing positive has to
        // fall in the range of [1, n + 1].
        // We ignore any values outside of [1, n] as 
        // they cannot affect the answer.
        // Place each i in [1, n] at the index i - 1.
        // O(n) work for outer loop and at most n
        // swaps are done. Ignoring duplicates, each
        // i has a unique destination index i - 1.
        for (int i = 0; i < nums.size(); ++i) {
            while (
                nums[i] >= 1
                && nums[i] <= nums.size()
                && nums[nums[i] - 1] != nums[i]) {
                swap(nums[nums[i] - 1], nums[i]);
            }
        }

        // If value x is present, it must be at
        // index x - 1.
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return nums.size() + 1;
    }
};