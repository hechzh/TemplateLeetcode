#include <iostream>
#include <vector>
#include <array>
#include <type_traits>
using namespace std;
class Solution{
	public:
		vector<int> getRow(int rowIndex){
			vector<int> Answer(rowIndex+1);
			int temp=0;
			Answer[0]=1;
			for(int i=0;i<rowIndex+1;i++){
				temp=0;
				for(int j=0;j<=i;j++){
					Answer[j]+=temp;
					temp=Answer[j]-temp;
				}
			}	
			return Answer;		
		}

};


template<int i,int j>
struct triangle{
	const static int value=triangle<i-1,j>::value+triangle<i,j-1>::value;
};

template<int i>
struct triangle<i,0>{
	const static int value=1;
};

template<int i>
struct triangle<0,i>{
	const static int value=1;
};

template<>
struct triangle<0,0>{
	const static int value =1;
};

template <size_t N,size_t ...I>
static constexpr auto Triangle(std::index_sequence<I...>) {
	constexpr std::array<int,N+1> nums = {triangle<I,N- I>::value ...};
	return nums;
}

template <size_t N>
constexpr static auto Triangle() {
	    return Triangle<N>(std::make_index_sequence<N+1>{});
}

int main(){
	Solution S;
	auto X=S.getRow(4);
	for(auto x:X){
	cout<<x<<" ";
	}
	cout<<endl;
	auto Y=Triangle<4>();
	for(auto y:Y){
		cout<<y<<" ";
	}
	cout<<endl;
	return 0;
}
