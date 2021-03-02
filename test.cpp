#include "RIPcomplex.h"
#include <iostream>
using namespace std;

void printM(vector<vector<int>> X){
	for(auto _x:X){
		for(auto _:_x){
			cout<<_<<" ";
		}
		cout<<endl;
	}cout<<endl;
}

int main(){
	Point a,b,c,d,e;
	//RIP test={{a},{b},{c},{d},{e},{a,b},{b,c},{c,d},{d,e},{c,e},{c,d,e}};
	if(1){
		cout<<"Test complex"<<endl;
		RIP test1={{a},{b},{c},{d},
		{a,b},{b,c},{a,c},{a,d},{b,d},{c,d},
		{a,b,c},{b,c,d},{a,b,d},{a,c,d}};
		auto M2=test1.EdgeOP(2);
		cout<<"M2:"<<endl;
		printM(M2);
		auto M1=test1.EdgeOP(1);
		cout<<"M1:"<<endl;
		printM(M1);
		auto M0=test1.EdgeOP(0);
		cout<<"M0:"<<endl;
		printM(M0);
		Rank(M0);
		cout<<"rank2:"<< Rank(M2) <<endl;
		printM(M2);
		cout<<"rank1:"<< Rank(M1) <<endl;
		printM(M1);
		cout<<"0 order homological group:"<< test1.Homo(0)<<endl;
		cout<<"1 order homological group:"<< test1.Homo(1)<<endl;
		cout<<"2 order homological group:"<< test1.Homo(2)<<endl;
	}
	if(1){
		cout<<"Test two connected parts:"<<endl;
		RIP test2={{a},{b},{c},{d},
		{a,b},{c,d}};
		auto M1=test2.EdgeOP(1);
		cout<<"M1:"<<endl;
		printM(M1);
		auto M0=test2.EdgeOP(0);
		cout<<"M0:"<<endl;
		printM(M0);
		cout<<"0 order homological group:"<< test2.Homo(0)<<endl;
		cout<<"1 order homological group:"<< test2.Homo(1)<<endl;
	}
	if(1){
		cout<<"Test RIP:"<<endl;
		RIP test3=generateRIP({a,b,c,d,e});
		cout<<"0 order homological group:"<< test3.Homo(0)<<endl;
		cout<<"1 order homological group:"<< test3.Homo(1)<<endl;
		cout<<"2 order homological group:"<< test3.Homo(2)<<endl;
		cout<<"3 order homological group:"<< test3.Homo(3)<<endl;
	}
}