/*
 * =====================================================================================
 *
 *       Filename:  AllPairsShortestPath.cpp
 *
 *    Description:  I will implement matrix multiplication
 *    Floyd-Warshall Johnson's algorithm
 *
 *        Version:  1.0
 *        Created:  2012年09月09日 17时02分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Graph.h"
#include <limits.h>
#include "TopSorting.h"
MatrixGraph Extend_shortest_path(const MatrixGraph& L,
		const MatrixGraph& w) {
	MatrixGraph Result(L);

	for( int i = 0 ; i < L.getSize() ; i++ )
	{
		for( int j = 0 ; static_cast<unsigned>(j) < L[i].size() ; j++ )
		{
			int min = INT_MAX;
			bool find = false;
			for( int k = 0 ; k < L.getSize() ; k++ )
			{
				if( L[i][k] != MaxDistance && w[k][j] != MaxDistance 
						&& min > L[i][k] + w[k][j] )
				{
					find = true;
					min = L[i][k] + w[k][j];
				}
			}
			if(find) 
				Result[i][j] = min;
		}
	}
	return Result;
	
}

MatrixGraph MatrixAPSP(const MatrixGraph& mG) {
	MatrixGraph result(mG);
	for( int i = 2 ; i < mG.getSize() ; i++ )
	{
		result = Extend_shortest_path(result, mG);
	}
	return result;
}

MatrixGraph MatrixAPSP2(const MatrixGraph& mG) {
	MatrixGraph result(mG);
	for( int i = 2 ; i < mG.getSize() ; i *= 2 )
	{
		result = Extend_shortest_path(result, result);
	}
	return result;
}

MatrixGraph FloydWarShall(const MatrixGraph& mG) {
	MatrixGraph result(mG);
	for( int k = 0 ; k < mG.getSize() ; k++ )
	{
		for( int i = 0 ; i < mG.getSize() ; i++ )
		{
			for( int j = 0 ; j < mG.getSize() ;
				   	j++ )
			{
				if( result[i][k] != MaxDistance && 
				 result[k][j] != MaxDistance && 
				 result[i][k] + result[k][j] < result[i][j] )
				{
					result[i][j] = result[i][k] + result[k][j];
				}
			}
			
		}
		
	}
	return result;
	
}

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

void printVV(const AdjacentGraph& vv) {
	for( int i = 0 ; i < vv.getSize() ; i++ )
	{
		for(int j = 0; static_cast<unsigned>(j) < vv[i].size(); j++)
			std::cout << vv[i][j].first << " " << vv[i][j].second << "\t";
		std::cout << std::endl;
	}
}
void printVV(const MatrixGraph& vv) {
	for( int i = 0 ; i < vv.getSize() ; i++ )
	{
		for(int j = 0; static_cast<unsigned>(j) < vv[i].size(); j++)
			std::cout << vv[i][j] << "\t";
		std::cout << std::endl;
	}
}
bool Johnson(const AdjacentGraph& aG, MatrixGraph& mG) {
	AdjacentGraph saG(aG.getSize() + 1);
	int k = aG.getSize();

	//add the Graph S vertice
	for( int i = 0 ; static_cast<unsigned>(i)
		   	< aG.getSize() ; i++ )
	{
		for( int j = 0 ; static_cast<unsigned>(j)
			   	< aG[i].size() ; j++ )
		{
			saG[i].push_back(aG[i][j]);
		}
	}

	for( int i = 0 ; i < aG.getSize() ; i++ )
	{
		saG[k].push_back(std::make_pair(i, 0));
	}


	//printVV(saG);
	std::vector<int> d, pai;
	bool noCircle = BellmanFord(saG, d, pai, k);
	if(noCircle == false) return false;
	//std::cout << "d:"<< d << std::endl;

	AdjacentGraph adjGNew(aG);

	//reweight the graph
	for( int i = 0 ; i < adjGNew.getSize() ; i++ )	{
		for( int j = 0 ; static_cast<unsigned>(j)
			   	< adjGNew[i].size() ; j++ )
		{
			adjGNew[i][j].second = d[i] + adjGNew[i][j].second
			   - d[adjGNew[i][j].first];	
		}
	}


	std::vector<int> newd;
	for( int i = 0 ; i < adjGNew.getSize()  ; i++ )
	{
		Dijkstra(adjGNew, newd, pai, i);
	//	std::cout << newd << std::endl;
		for( int j = 0 ; j < adjGNew.getSize() ; j++ )
		{
			mG[i][j] = newd[j] + d[j] - d[i]; 
		}
	}

	return true;
}
int main(int argc, char *argv[])
{
	MatrixGraph mG("Graph-10.txt");

	std::cout << MatrixAPSP(mG) << std::endl;

	std::cout << MatrixAPSP2(mG) << std::endl;

	std::cout << FloydWarShall(mG);

	MatrixGraph mG1(mG.getSize());
	AdjacentGraph aG("Graph-10.txt");

	std::cout << Johnson(aG, mG1) << std::endl;
	printVV(mG1);
	return 0;
}
