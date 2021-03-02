#pragma once
#include <map>
#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define POINTSMAXNUM 20

static int counting=0;

struct Point
{
	int index;
	double pos;
	Point():index(counting),pos(0){counting+=1;}
	Point(double x):index(counting),pos(0){counting+=1;}
};

double Distance(Point a,Point b){return a.pos-b.pos;}

int getindex(const initializer_list<Point>& A){
	int sum=0;
	for(auto p:A){
		sum+=(1<<p.index);
	}
	return sum;
}

int getindex(const vector<Point>& A){
	int sum=0;
	for(auto p:A){
		sum+=(1<<p.index);
	}
	return sum;
}

int Rank(vector<vector<int>> M){
	if(M.size()==0) return 0;
	int i=0,j=0;
	int R=M.size(),C=M[0].size();
	while(i<R && j<C){
		if(M[i][j]==0){
			int flag=0,k=i;
			while(k<R){
				if(M[k][j]==1){
					flag=1;
					auto temp=M[k];
					M[k]=M[i];
					M[i]=temp;
					break;
				}
				k++;
			}
			if(flag==0) j++;
		}
		else{
			int flag=0,k=i+1;
			while(k<R){
				if(M[k][j]==1){
					for(int c=j;c<C;c++){
						M[k][c]^=M[i][c];
					}
				}
				k++;
			}
			i++;
		}
	}
	return i;
}

struct RIP
{
	vector<vector<int>> simplex;
	map<int,int> index;
	vector<int> _indexCounter;//an index counter
	RIP():simplex(POINTSMAXNUM),_indexCounter(POINTSMAXNUM,0){};

	RIP(const initializer_list<initializer_list<Point>>& A)
	:simplex(POINTSMAXNUM),_indexCounter(POINTSMAXNUM,0){
		for(auto M:A){
			int Mindex=getindex(M);
			index[Mindex]=_indexCounter[M.size()];
			simplex[M.size()].push_back(Mindex);
			_indexCounter[M.size()]+=1;
		}
	};

	RIP(const vector<vector<Point>>& A)
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

	void Add(const vector<Point>& M){
		int Mindex=getindex(M);
		index[Mindex]=_indexCounter[M.size()];
		simplex[M.size()].push_back(Mindex);
		_indexCounter[M.size()]+=1;
	};

	vector<vector<int>> EdgeOP(int Z){
		int N=Z+1;
		int R=_indexCounter[N];
		if(_indexCounter[Z]==0) {
			vector<vector<int>> Answer(1,vector<int>(R));
			return Answer;
		}
		int C=_indexCounter[N-1];
		vector<vector<int>> Answer(R,vector<int>(C));
		int temp=0;
		for(auto s:simplex[N]){
			while(temp<POINTSMAXNUM){
				if( s&(1<<temp) ){
					Answer[index[s]][index[s-(1<<temp)]]=1;
				}
				temp++;
			}
			temp=0;
		}
		return Answer;
	};

	int Homo(int M){return _indexCounter[M+1]-Rank(move(EdgeOP(M)))-Rank(move(EdgeOP(M+1)));}
};

bool check(vector<Point> Pointvector,vector<vector<int> > VCLOSE){
	int i=0,j=0;
	if(!Pointvector.size()) return true;
	for(;i<Pointvector.size();i++){
		for(j=0;j<Pointvector.size();j++){
			int it=Pointvector[i].index;
			if (find(VCLOSE[it].begin(),VCLOSE[it].end(),Pointvector[i].index)==VCLOSE[it].end())
				return false;
		}
	}
	return true;
}

vector<Point> indexlet(vector<Point> v,int index){
	vector<Point> Answer;
	for(int i=0;i<v.size() && index>0;i++){
		if(index%2) Answer.push_back(v[i]);
		index/=2;
	}
	return Answer;
}

RIP generateRIP(initializer_list<Point> A,double threshold=1){
	int S=A.size();
	vector<Point> v=A;
	int i=0,j=0;
	vector<vector<int>> vClose(POINTSMAXNUM,vector<int>());
	vector<vector<Point>> Answer_gen;
	while(i<S){
		int it=v[i].index;
		while(j<S){
			if(Distance(v[i],v[j])<threshold) vClose[it].push_back(v[j].index);
			j++;
		}
		j=0;
		i++;
	}
	int iter=1;
	while(iter<pow(2,S)){
		auto now_vec=indexlet(v,iter);
		if (check(now_vec,vClose)){
			Answer_gen.push_back(now_vec);
		}
		iter++;
	}
	RIP Answer({Answer_gen});
	return Answer;
}

