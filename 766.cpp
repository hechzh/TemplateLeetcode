#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        int ybound=matrix.size();
        int xbound=matrix[0].size();
        if(xbound==1 || ybound==1) return true;
        int x=xbound-1,y=0,temp=0;
        while(1){
            if(x+1<xbound && y+1<ybound){
                x++;y++;
                if(matrix[y][x]!=temp) return false;
            }else{
                if (x-y>0){
                    x=x-y-1;
                    y=0;
                }else{
                    if(y-x+1==ybound-1) break;
                    y=y-x+1;
                    x=0;
                }
                temp=matrix[y][x];
            }
        }
        return true;
    }
};



template <int... Ints>
using int_sequence = integer_sequence<int, Ints...>;

template <int I, int... N>
constexpr auto cat(int_sequence<N...>) { return int_sequence<I, N...>(); }

template <int I, int... N>
void print(int_sequence<I, N...>)
{
    cout << I << " ";
    if constexpr (sizeof...(N) == 0)
        cout << endl;
    else
        print(int_sequence<N...>());
}


template <int Itop, int... I>
constexpr int gethead(int_sequence<Itop, I...>) { return Itop; }

template <int index, int Itop, int... I>
constexpr int getvalue(int_sequence<Itop, I...>)
{
    if constexpr (index == 0)
        return Itop;
    else
        return getvalue<index - 1>(int_sequence<I...>());
}

template <int row, int columns, int... I>
struct Matrix
{
public:
    static const int r = row;
    static const int c = columns;
    template <int i, int j>
    static const int value = getvalue<i * columns + j>(int_sequence<I...>());
};

template<int Itop,int... I>
constexpr bool checkequal(int_sequence<Itop,I...>){return ((Itop == I) &&...);}

template<int x,int y,int row,int columns,int ...I>
constexpr auto getxToeplitz(const Matrix<row,columns,I...> _){
    if constexpr (x<row && y<columns)
    {
        return cat< getvalue<x*columns+y>(int_sequence<I...>()) >(getxToeplitz<x+1,y+1>(_));
    }else{
        return int_sequence<>();
    }
}


template<int num,int row,int columns,int... I>
constexpr bool checkToeplitzMatrix(Matrix<row,columns,I...> _){
    if constexpr(num<0) return checkequal(getxToeplitz<-num,0>(_)) && checkToeplitzMatrix<num+1>(_);
    else{
        if constexpr(num>columns-2) return true;
        else{
            return checkequal(getxToeplitz<0,num+1>(_)) && checkToeplitzMatrix<num+1>(_);
        }
    }
}

template<int row,int columns,int... I>
constexpr bool isToeplitzMatrix(Matrix<row,columns,I...> _){
    if constexpr(row==1 || columns==1) return true;
    else{
        return checkToeplitzMatrix<2-row>(_);
    }
}




int main(){
    Solution s;
    vector<vector<int>> test={{1,2,3,4},{5,1,2,3},{9,5,1,2}};
    bool result=s.isToeplitzMatrix(test);
    cout<<result<<endl;
    auto template_test=Matrix<3,4,1,2,3,4,5,1,2,3,9,5,1,2>();
    bool template_result=isToeplitzMatrix(template_test);
    cout<<template_result<<endl;
}