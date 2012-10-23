/*
 * =====================================================================================
 *
 *       Filename:  SingleSourceShortestPath.cpp
 *
 *    Description:  implement Bellman-Ford & Dag & Dijkstra algorithm
 *
 *        Version:  1.0
 *        Created:  2012年09月09日 09时50分25秒
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
#include "TopSorting.h"
/*  
std::ostream& operator<<( std::ostream& out, const std::vector<int>& vi) {
	for( int i = 0 ; static_cast<unsigned>(i) < vi.size() ; i++ )
	{
		out << "\t" << vi[i] ;
	}

	out << std::endl;
	return out ;	
}*/

const int MAX = 10000;
void initSSSP(const AdjacentGraph& aG, std::vector<int>& d, 
		std::vector<int>& pai, int s) {
	d.resize(aG.getSize());
	pai.resize(aG.getSize());
	d.assign(aG.getSize(), MAX);
	pai.assign(aG.getSize(), -1);
	d[s] = 0;
}

bool BellmanFord(const AdjacentGraph& aG, std::vector<int>& d, 
		std::vector<int>& pai, int s) {

	initSSSP(aG, d, pai, s);

	for( int i = 0 ; i < aG.getSize() - 1 ; i++ )
	{
		for( int j = 0 ; j < aG.getSize() ; j++ )
		{
			for( int k = 0 ; static_cast<unsigned>(k) 
					< aG[j].size() ; k++ )
			{
				edge e = aG[j][k];
				if(d[e.first] > d[j] + e.second) {
					pai[e.first] = j;
					d[e.first] = d[j] + e.second;
				}
			}
		}
		
	}

	//check negative circles
	for( int i = 0 ; i < aG.getSize() ; i++ )
	{
		for( int j = 0 ; static_cast<unsigned>(j) < aG[i].size() ; j++ )
		{
			edge e = aG[i][j];
			if( d[i] + e.second < d[e.first] )
			{
				return false;
			}
		}
	}
	return true;	
}

void DagSSSP(const AdjacentGraph& aG, std::vector<int>& d,
		std::vector<int>& pai, int s) {
	std::vector<int> toplogical;
	topologicalSort(aG, toplogical);
	d[s] = 0;
	initSSSP(aG, d, pai, s);
	for( int i = 0 ; static_cast<unsigned>(i) < toplogical.size() ;
		   	i++ )
	{
		int vertice = toplogical[i];
		for( int j = 0 ; static_cast<unsigned>(j) < aG[vertice].size() ;
			   j++ )
		{
			edge e = aG[vertice][j];
			if(d[vertice] + e.second < d[e.first]) {
				d[e.first] = d[vertice] + e.second;
				pai[e.first] = vertice;
			}
		}
		
	}
}

void Dijkstra(const AdjacentGraph& aG, std::vector<int>& d,
		std::vector<int>& pai, int s) {
	std::vector<bool> added(aG.getSize(), false);
	initSSSP(aG, d, pai, s);

	for( int i = 0 ; i < aG.getSize() - 1 ; i++ )
	{
		int min = -1;
		for( int j = 0 ; static_cast<unsigned>(j) < d.size() ; j++ )
		{
			if( added[j] == false && (min == -1 || d[min] > d[j]) )
			{
				min = j;
			}
		}
		added[min] = true;

		for( int j = 0 ; static_cast<unsigned>(j) < aG[min].size() ; j++ )
		{
			edge e = aG[min][j];
			if(added[e.first] == false && 
					d[min] + e.second < d[e.first]){
				d[e.first] = d[min] + e.second;
				pai[e.first] = min;
			}
		}
	}
}
int main(int argc, char *argv[])
{
	AdjacentGraph aG("Graph-7.txt");
	std::vector<int> d, pai;
	BellmanFord(aG, d, pai, 0);

	std::cout << d << std::endl;
	std::cout << pai << std::endl;	

	AdjacentGraph dag("Graph-8.txt");
	DagSSSP(dag, d, pai, 1);
	std::cout << d << std::endl;
	std::cout << pai << std::endl;

	std::cout << "dijkstra" << std::endl;
	AdjacentGraph dijkstra("Graph-9.txt");
	Dijkstra(dijkstra, d, pai, 0);
	std::cout << d << std::endl;
	std::cout << pai << std::endl;
	return 0;
}
