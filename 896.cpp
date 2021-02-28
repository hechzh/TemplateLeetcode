class Solution {
public:
    bool isMonotonic(vector<int>& A) {
        bool flagA=1,flagB=1;
        int k=A.size();
        if(k<2) return true;
        else{
            for(int i=1;i<k && (flagA|| flagB) ;i++){
                if(A[i]-A[i-1]>0){
                    flagB=0;
                }else{
                    if (A[i]-A[i-1]<0) flagA=0;
                }
            }
            return flagA||flagB;
        }
        
    }
};