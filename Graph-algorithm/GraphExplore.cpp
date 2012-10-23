/*
 * =====================================================================================
 *
 *       Filename:  GraphExplore.cpp
 *
 *    Description:  implement bfs&dfs for graph depict in adjacent list
 *
 *        Version:  1.0
 *        Created:  2012年09月07日 11时13分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Graph.h"
#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>
const int White = 0;
const int Gray = 1;
const int Black = 2;
const int NotAcess = INT_MAX;
const int nil = -1;

std::ostream& operator<<( std::ostream& out, const std::vector<int>& vi) {
	for( int i = 0 ; static_cast<unsigned>(i) < vi.size() ; i++ )
	{
		out << "\t" << vi[i] ;
	}

	out << std::endl;
	return out ;	
}
void BFS(const AdjacentGraph& adjG) {
	std::vector<int> colors(adjG.getSize(), White);
	std::vector<int> d(adjG.getSize(), NotAcess);
	std::vector<int> pai(adjG.getSize(), nil);

	colors[0] = Gray;
	d[0] = 0;
	pai[0] = nil;

	std::queue<int> Q;
	Q.push(0);
	
	std::cout << "visit " << adjG.getVerticeName(0) << std::endl;

	while(!Q.empty()) {
		int vertice = Q.front();
		Q.pop();
		for( int i = 0 ; static_cast<unsigned>(i) < adjG[vertice].size() ;
			   	i++ )
		{
			edge e = adjG[vertice][i];
			if(colors[e.first] == White) {
				colors[e.first] = Gray;
				d[e.first] = d[vertice] + 1;
				pai[e.first] = vertice;
				Q.push(e.first);
				std::cout << "visit " << adjG.getVerticeName(e.first) << std::endl;
			}
		}
		colors[vertice] = Black;
	}
}

typedef std::vector<int> veci;
void DFSAuxliary(const AdjacentGraph& adjG, veci &color,
		veci& d, veci& pai, veci& finish, int start, int& time) ;

void DFS(const AdjacentGraph& adjG) {
	std::vector<int> colors(adjG.getSize(), White);
	std::vector<int> d(adjG.getSize(), NotAcess);
	std::vector<int> pai(adjG.getSize(), nil);
	std::vector<int> finish(adjG.getSize(), NotAcess);
	int time = 1;

	for( int i = 0; i < adjG.getSize(); i++ ) {
		if(colors[i] == White) {
			colors[i] = Gray;
			d[i] = time;
			time += 1;
			pai[i] = nil;
			std::cout << "visit " << i << std::endl;
			DFSAuxliary(adjG, colors, d, pai, finish, i, time);
		}
	}

	std::cout << "start " << d << std::endl;
	std::cout << "finish " << finish << std::endl;

}

void DFSAuxliary(const AdjacentGraph& adjG, veci &color,
		veci& d, veci& pai, veci& finish, int start, int& time) {
	for( int i = 0 ; static_cast<unsigned>(i) < adjG[start].size() ; i++ )
	{
		edge e = adjG[start][i];
		if(color[e.first] == White) {
			d[e.first] = time;
			time += 1;

			color[e.first] = Gray;
			pai[e.first] = start;

			std::cout << "visit " << e.first << std::endl;
			DFSAuxliary(adjG, color, d, pai, finish, e.first, time);
		}
	}
	color[start] = Black;
	finish[start] = time;
	time += 1;
}


int main(int argc, char *argv[])
{
	AdjacentGraph adjG("Graph-2.txt");

	std::cout << adjG;

	BFS(adjG);

	std::cout << "\n\n\n";
	DFS(adjG);

	AdjacentGraph adjG1("Graph-3.txt");

	std::cout << adjG1;

	BFS(adjG1);

	std::cout << "\n\n\n";
	DFS(adjG1);

	return 0;
}
