class NumArray {
public:
    vector<int> sums;
    NumArray(vector<int>& nums) {
        sums=vector<int>(nums.size());
        int temp=0;
        for(int i=0;i<nums.size();i++){
            temp+=nums[i];
            sums[i]+=temp;
        }
    }
    
    int sumRange(int i, int j) {
        if (i==0) return sums[j];
        else return sums[j]-sums[i-1];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */

