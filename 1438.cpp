#include <iostream>
#include <vector>
#include <set>

#define TEST_CASE_1438 10,1,2,3,3,7,2,4

using namespace std;

class Solution {
public:
	int longestSubarray(vector<int>& nums, int limit) {
		multiset<int> window;
		for (int left = 0, right = 0; right < nums.size(); ++right) {
			window.insert(nums[right]);
			if (*window.rbegin() - *window.begin() > limit)
				window.erase(window.find(nums[left++]));
		}
		return window.size();
	}
};

template <int... Ints>
using int_sequence = std::integer_sequence<int, Ints...>;

constexpr int Maxnum(int_sequence<>){return 0;}
constexpr int Minnum(int_sequence<>){return 0;}

template<int num,int Itop,int...I>
constexpr int Maxnum(int_sequence<Itop,I...>){
	if constexpr (sizeof...(I)==0) return max(num,Itop);
	else return Maxnum<(num>Itop?num:Itop)>(int_sequence<I...>());
}

template<int num,int Itop,int...I>
constexpr int Minnum(int_sequence<Itop,I...>){
	if constexpr (sizeof...(I)==0) return min(num,Itop);
	else return Minnum<(num<Itop?num:Itop)>(int_sequence<I...>());
}

template<int Itop,int... I>
constexpr int head(int_sequence<Itop,I...>){return Itop;}

template<int Itop,int... I>
constexpr auto tail(int_sequence<Itop,I...>){return int_sequence<I...>();}

template<int...I>
constexpr int Maxnum(int_sequence<I...> _){
	return Maxnum<head(_)>(_);
}

template<int...I>
constexpr int Minnum(int_sequence<I...> _){
	return Minnum<head(_)>(_);
}

template <int I, int... N>
void print(int_sequence<I, N...>)
{
    cout << I << " ";
    if constexpr (sizeof...(N) == 0)
        cout << endl;
    else
        print(int_sequence<N...>());
}


template<int limit,int L,int ...J>
constexpr int longestSubarray(int_sequence<J...>,int_sequence<> ){return L;}

template<int limit,int L,int Itop,int ...J,int... I>
constexpr int longestSubarray(int_sequence<J...> _,int_sequence<Itop,I...> m){
	if constexpr(Maxnum(_)-Minnum(_)>limit) 
		return longestSubarray<limit,L>(tail(_),m);
	else{
		if constexpr(sizeof...(J)+1>L)
			return longestSubarray<limit,(sizeof...(J)+1)>(int_sequence<J...,Itop>(),int_sequence<I...>());
		else
			return longestSubarray<limit,L>(int_sequence<J...,Itop>(),int_sequence<I...>());
	}
}

template<int limit,int Itop,int ...I>
constexpr int longestSubarray(int_sequence<Itop,I...> _){return longestSubarray<limit,0>(int_sequence<>(),_);}


int main(){
	Solution s;
	constexpr int limit=5;
	vector<int> test={TEST_CASE_1438};
	int result=s.longestSubarray(test,limit);
	cout<<result<<endl;
	auto template_test=int_sequence<TEST_CASE_1438>();
	int template_result=longestSubarray<limit>(template_test);
	cout<< template_result <<endl;
	return 1;
}