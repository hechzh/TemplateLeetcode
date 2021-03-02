class NumMatrix {
public:
    vector<vector<int>> V;
    NumMatrix(vector<vector<int>>& matrix) {
        if(matrix.size()==0) return;
        int temp=0;
        int R=matrix.size(),C=matrix[0].size();
        V=vector<vector<int>>(R+1,vector<int>(C+1));
        for(int i=1;i<R+1;i++){
            temp=0;
            for(int j=1;j<C+1;j++){
                temp+=matrix[i-1][j-1];
                V[i][j]=V[i-1][j]+temp;
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return V[row2+1][col2+1]-V[row1][col2+1]-V[row2+1][col1]+V[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */