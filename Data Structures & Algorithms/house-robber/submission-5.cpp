class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) {
            return nums[0];
        }
        
        int notRobbedPrev = nums[0];
        int robbedPrev = nums[1];
        for (int i = 2; i < n; ++i) {
            int oldRobbedPrev = robbedPrev;
            robbedPrev = notRobbedPrev + nums[i];
            notRobbedPrev = max(notRobbedPrev, oldRobbedPrev);
        }       
        return max(notRobbedPrev, robbedPrev);
    }
};
