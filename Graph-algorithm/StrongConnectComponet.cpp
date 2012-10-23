/*
 * =====================================================================================
 *
 *       Filename:  StrongConnectComponet.cpp
 *
 *    Description:  compute strong connected component
 *                  here we need to customize the DFS, 
 *                  and get the transpose of the Graph
 *
 *        Version:  1.0
 *        Created:  2012年09月08日 17时06分57秒
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

typedef std::vector<int> veci;
void DFSAuxliary(const AdjacentGraph& adjG, veci &color,
		veci& d, veci& pai, veci& finish, int start, int& time, bool showVist) ;

veci DFS(const AdjacentGraph& adjG) {
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
			//std::cout << "visit " << i << std::endl;
			DFSAuxliary(adjG, colors, d, pai, finish, i, time, false);
		}
	}

	//std::cout << "start " << d << std::endl;
	//std::cout << "finish " << finish << std::endl;

	return finish;

}

void DFSAuxliary(const AdjacentGraph& adjG, veci &color,
		veci& d, veci& pai, veci& finish, int start, int& time, bool showVist) {
	for( int i = 0 ; static_cast<unsigned>(i) < adjG[start].size() ; i++ )
	{
		edge e = adjG[start][i];
		if(color[e.first] == White) {
			d[e.first] = time;
			time += 1;

			color[e.first] = Gray;
			pai[e.first] = start;
			if(showVist)
				std::cout << e.first << " ";
			DFSAuxliary(adjG, color, d, pai, finish, e.first, time, showVist);
		}
	}
	color[start] = Black;
	finish[start] = time;
	time += 1;
}

void SCC(const AdjacentGraph& adjG) {

	std::vector<int> colors(adjG.getSize(), White);
	std::vector<int> d(adjG.getSize(), NotAcess);
	std::vector<int> pai(adjG.getSize(), nil);
	std::vector<int> finish(adjG.getSize(), NotAcess);
	int time = 1;
	veci fin = DFS(adjG);
	typedef std::pair<int, int> finishVer;
	std::vector<finishVer> vfv;
	for( int i = 0 ; static_cast<unsigned>(i) < fin.size() ; i++ )
	{
		vfv.push_back(std::make_pair(fin[i], i));
	}

	std::sort(vfv.begin(), vfv.end());

	//make it decreasing
	for( int i = 0, j = vfv.size()-1 ; i < j ; i++, j-- )
	{
		std::swap(vfv[i], vfv[j]);
	}
	
	AdjacentGraph trans(adjG);
	trans.transpose();

	for( int i = 0 ; static_cast<unsigned>(i) < vfv.size() ; i++ )
	{ 
		int n = vfv[i].second;
		if( colors[n] == White )
		{
			colors[n] = Gray;
			d[n] = time;
			time += 1;
			std::cout << "new SCC set: " << n << " ";
			DFSAuxliary(trans, colors, d, pai, finish, n, time, true);
			std::cout << std::endl;
		}
	}
}
int main(int argc, char *argv[])
{

	AdjacentGraph aG("Graph-5.txt");
	SCC(aG);

	return 0;
}
