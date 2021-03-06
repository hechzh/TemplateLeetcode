class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int i=0,S=nums.size();
        vector<int> T;
        vector<int> Answer(S);
        while(i<S){
                while(T.size()&&nums[i]>nums[T.back()]){
                    Answer[T.back()]=nums[i];
                    T.pop_back();
                }
            T.push_back(i);
            i++;
        }
        i=0;
        while(i<S&& T.size()){
            while(nums[i]>nums[T.back()]){
                Answer[T.back()]=nums[i];
                T.pop_back();
            }
            i++;
        }
        if(T.size()){
            for(auto j:T)
                Answer[j]=-1;
        }
        return Answer;
    }

};