#include <iostream>
#include <vector>

using namespace std;

#define TEST_1052_C 1,0,1,2,1,1,7,5
#define TEST_1052_g 0,1,0,1,0,1,0,1
#define TEST_1052_x 3

class Solution {
public:
	int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
		if(X>=grumpy.size()){
			int sum=0;
			for(auto i:customers)
				sum+=i;
			return sum;
		}
		int left=0,sumc=0,sumg=0,right=0;
		while(right<X){
			if(!grumpy[right])
				sumc+=customers[right];
			else{
				sumg+=customers[right];
			}
			right++;
		}
		int maxg=sumg;
		while(right<grumpy.size())
		{
			if(grumpy[left])
				sumg-=customers[left];
			if(!grumpy[right])
				sumc+=customers[right];
			else{
				sumg+=customers[right];
				maxg=max(sumg,maxg);
			}
			left++;right++;
		}
		return sumc+maxg;
	}
};

template <int... Ints>
using int_sequence = integer_sequence<int, Ints...>;

template <int Itop, int... I>
constexpr int head(int_sequence<Itop, I...>) { return Itop; }

template <int Itop, int... I>
constexpr auto tail(int_sequence<Itop, I...>) { return int_sequence<I...>(); }

template <int I, int... N>
constexpr auto cat(int_sequence<N...>) { return int_sequence<I, N...>(); }

template<int...I,int...J>
constexpr int doSatisfiedDot(int_sequence<I...> a,int_sequence<J...> b){
	if constexpr(sizeof...(I)==0)
		return 0;
	else
		return head(a)*(1-head(b))+doSatisfiedDot(tail(a),tail(b)); 
};

template<int... I,int... J>
constexpr auto doDot(int_sequence<I...> a,int_sequence<J...> b){
	if constexpr(sizeof...(I)==0) 
		return int_sequence<>();
	else 
		return cat<head(a)*head(b)>(doDot(tail(a),tail(b)));
}

template<int X,int... I,int... J>
constexpr int doSum(int_sequence<I...> a){
	if constexpr(X==0 || sizeof...(I)==0) 
		return 0;
	else 
		return head(a)+doSum<X-1>(tail(a));
}

template<int X,int... I,int... J>
constexpr int doSumLoop(int_sequence<I...> a){
	if constexpr(sizeof...(I)==0)
		return 0;
	else
		return max(doSum<X>(a),doSumLoop<X>(tail(a)));
}

template<int X,int... I,int... J>
constexpr int maxSatisfied(int_sequence<I...> a,int_sequence<J...> b){
	return doSatisfiedDot(a,b)+doSumLoop<X>(doDot(a,b));
}

int main(){
	Solution s;
	vector<int> test_c={TEST_1052_C};
	vector<int> test_g={TEST_1052_g};
	int X=TEST_1052_x;
	int result=s.maxSatisfied(test_c,test_g,X);
	cout<<result<<endl;
	auto template_c=int_sequence<TEST_1052_C>();
	auto template_g=int_sequence<TEST_1052_g>();
	auto template_result=maxSatisfied<TEST_1052_x>(template_c,template_g);
	cout<<template_result<<endl;
}