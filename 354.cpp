bool cmp(vector<int>& a,vector<int>& b){
    if(a[0]<b[0]){
        return 1;
        }
    else{
        if(a[0]==b[0] && a[1]>b[1]) 
            return 1;
        return 0;
    }
}

int lengthOfLIS(vector<int>& nums) {
        int len = 1, n = (int)nums.size();
        if (n == 0) {
            return 0;
        }
        vector<int> d(n + 1, 0);
        d[len] = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > d[len]) {
                d[++len] = nums[i];
            } else {
                int l = 1, r = len, pos = 0,mid = 0;
                while (l <= r) {
                    mid = (l + r) >> 1;
                    if (d[mid] < nums[i]) {
                        pos = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                d[pos + 1] = nums[i];
            }
        }
        return len;
}

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(),envelopes.end(),cmp);
        vector<int> A(envelopes.size());
        int i=0;
        int j=0;
        for(auto a:envelopes){
            A[i]=a[1];
            i++;
        }
        return lengthOfLIS(A);
    }
};

