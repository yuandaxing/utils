/*
 * =====================================================================================
 *
 *       Filename:  MinSpanningTree.cpp
 *
 *    Description: implement Kruskal's algorithm & Prim's algorithm 
 *
 *        Version:  1.0
 *        Created:  2012年09月08日 21时41分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Graph.h"
#include <vector>
#include <limits.h>
const int MaxVertice = 1000;
int father[MaxVertice] = {0};
//maybe logN
bool isSameSet(int i, int j) {
	while( father[i] != i )
	{
		i = father[i];
	}

	while( father[j] != j )
	{
		j = father[j];
	}

	return i == j;
}

void unionSet(int i, int j) {
	while( father[i] != i )
	{
		i = father[i];
	}

	while( father[j] != j )
	{
		j = father[j];
	}

	father[j] = i;
}

struct CEdge{
	int u_, v_;
	int w_;
	CEdge(int u, int v, int w) :
		u_(u), v_(v), w_(w) { }
};

std::ostream& operator<<(std::ostream& out, 
		const std::vector<CEdge>& vCE) {
	for( int i = 0 ; static_cast<unsigned>(i) < vCE.size() ; i++ )
	{
		std::cout <<"\t"<< vCE[i].u_ << " " 
			<< vCE[i].v_ << " " << vCE[i].w_;
	}
	
	return out;
}
//how to solve this weird bug
bool comCEdge(const CEdge& l, const CEdge& r) {
	return l.w_  <  r.w_ ;
	//return l.w_ -  r.w_ ;
}
int Kruskal(const AdjacentGraph& aG, 
		std::vector<CEdge>& treeEdge) {
	for( int i = 0 ; i < aG.getSize() ; i++ )
	{
		father[i] = i;
	}

	std::vector<CEdge> vCE;
	for( int i = 0 ; i < aG.getSize() ; i++ )
	{
		for( int j = 0 ; static_cast<unsigned>(j) < aG[i].size() ; j++ )
		{
			vCE.push_back(CEdge(i, aG[i][j].first, 
						aG[i][j].second));
		}
	}

	std::sort(vCE.begin(), vCE.end(), comCEdge);

	int sum = 0;
	for( int i = 0 ; static_cast<unsigned>(i) < vCE.size() ; i++ )
	{
		if(!isSameSet(vCE[i].u_, vCE[i].v_)) {
			treeEdge.push_back(vCE[i]);
			unionSet(vCE[i].u_, vCE[i].v_);
			sum += vCE[i].w_;
		}
	}
	return sum;
}


int Prime(const AdjacentGraph& aG, std::vector<CEdge>& vCE) {
	std::vector<bool> visited(aG.getSize(), false);
	std::vector<int> d(aG.getSize(), INT_MAX);
	std::vector<CEdge> cur(aG.getSize(), CEdge(0, 0, 0));
	
	d[0] = 0;
	int sum = 0;

	for( int i = 0 ; i < aG.getSize() ; i++ )
	{
		int min = -1;
		for( int j = 0 ; j < aG.getSize() ; j++ )
		{
			if(visited[j] == false && (min == -1 
						|| d[min] > d[j])) {
				min = j;
			}
		}
		visited[min] = true;
		sum += d[min];
		vCE.push_back(cur[min]);

		for( int j = 0 ; static_cast<unsigned>(j) < aG[min].size() ; j++ )
		{
			edge e = aG[min][j];
			if( visited[e.first] == false && e.second < d[e.first] )
			{
				d[e.first] = e.second;
				cur[e.first] = CEdge(j, e.first, e.second);
			}
		}
	}
	return sum;
}
int main(int argc, char *argv[])
{
	AdjacentGraph aG("Graph-6.txt");
	std::cout << aG << std::endl;
	std::vector<CEdge> ESet;
	int sum = Kruskal(aG, ESet);
	std::cout << sum << std::endl;
	std::cout << ESet << std::endl;

	ESet.clear();
	sum = Prime(aG, ESet);
	std::cout << sum << std::endl;
	std::cout << ESet << std::endl;
	return 0;
}
