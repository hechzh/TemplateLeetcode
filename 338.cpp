#include <iostream>
#include <vector>
#include <array>
using namespace std;

template <size_t i>
struct PopCount{
    constexpr static int value=PopCount<i/2>::value+i%2;
};

template <>
struct PopCount<0>{
    constexpr static int value=0;
};

template <size_t ...I>
constexpr auto precount(index_sequence<I...>){
	constexpr array<int,sizeof...(I)> Answer={PopCount<I>::value ...};
    return Answer;
}

class Solution {
public:
    constexpr static auto V=precount(make_index_sequence<1000>());
    vector<int> countBits(int num) {
        if(num<1000) return vector<int>(V.begin(),V.begin()+num+1);
        else{
            vector<int> Answer(num+1);
            for(int i=1;i<num+1;i++){
                Answer[i]=Answer[i>>1]+i%2;
            }
            return Answer;
        }
    }
};

int main(){
	auto A=precount(make_index_sequence<85723>());
	vector<int> B(A.begin(),A.end());
	cout<<B.size()<<endl;
	return 1;
}