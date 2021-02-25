#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int r=matrix.size();
        if (r){
            int c=matrix[0].size();
            vector<vector<int>> Answer(c,vector<int>(r));
            for(int j=0;j<r;j++){
                for(int i=0;i<c;i++)
                    Answer[i][j]=matrix[j][i];
            }
            return Answer;
        }
        else{
            return vector<vector<int>>();
        }
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

template <int index = 0, int... I>
void printN(Matrix<I...> _)
{
    if constexpr (index >= _.r * _.c)
        return;
    else
    {
        cout << getvalue<index + 2>(int_sequence<I...>()) << " ";
        if constexpr ((index + 1) % _.c == 0)
            cout << endl;
        printN<index + 1>(_);
    }
}

template<int row,int columns, int ...I>
auto make_matrix(int_sequence<I...>){
    return Matrix<row,columns,I...>();
}

template <int index = 0, int... I>
auto transpose2list(Matrix<I...> _)
{
    if constexpr (index >= _.r * _.c)
        return int_sequence<>();
    else
    {
        constexpr int number=getvalue<(index/_.c)+(index%_.c)*_.c+2>(int_sequence<I...>());
        return cat<number>(transpose2list<index+1>(_));
    }
}

template<int... I>
auto transpose(Matrix<I...> _){
    return make_matrix<_.r,_.c>(transpose2list(_));
}


int main(){
    Solution s;
    vector<vector<int>> test={{1,0,0},{0,1,0},{0,1,1}};
    auto result=s.transpose(test);
    for(auto i:result){
        for (auto j:i)
            cout<<j<<" ";
        cout<<endl;
    }
    cout<<endl;
    auto template_test=Matrix<3,3,1,0,0,0,1,0,0,1,1>();
    printN(template_test);
    cout<<endl;
    auto template_result=transpose(template_test);
    printN(template_result);
    return 1;
}