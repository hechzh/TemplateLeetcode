#pragma once
#include <map>
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

#define POINTSMAXNUM 5

static int counting=0;

struct Point
{
	int index;
	Point():index(counting){counting+=1;}
};

int getindex(const initializer_list<Point>& A){
	int sum=0;
	for(auto p:A){
		sum+=(1<<p.index);
	}
	return sum;
}

struct RIP
{
	vector<vector<int>> simplex;
	map<int,int> index;
	vector<int> _indexCounter;//an index counter
	RIP();
	RIP(const initializer_list<initializer_list<Point>>& A)
	:simplex(POINTSMAXNUM),_indexCounter(POINTSMAXNUM,0){
		for(auto M:A){
			int Mindex=getindex(M);
			index[Mindex]=_indexCounter[M.size()];
			simplex[M.size()].push_back(Mindex);
			_indexCounter[M.size()]+=1;
		}
	};
	void Add(const initializer_list<initializer_list<Point>>& A){
		for(auto M:A){
			int Mindex=getindex(M);
			index[Mindex]=_indexCounter[M.size()];
			simplex[M.size()].push_back(Mindex);
			_indexCounter[M.size()]+=1;
		}
	};
	vector<vector<int>> EdgeOP(int N){
		int R=_indexCounter[N];
		if(N==1) return vector<vector<int>>(1,vector<int>(R));
		int C=_indexCounter[N-1];
		vector<vector<int>> Answer(R,vector<int>(C));
		int temp=0;
		int ai=1;
		for(auto s:simplex[N]){
			//cout<<s<<endl;
			while(temp<POINTSMAXNUM){
				//cout<<temp<<endl;
				//cout<<(s&(1<<temp))<<endl;
				if( s&(1<<temp) ){
					Answer[index[s]][index[s-(1<<temp)]]=ai;
					ai*=-1;
				}
				temp++;
			}
			temp=0;ai=1;
		}
		return Answer;
	};
};

