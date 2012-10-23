/*
 * =====================================================================================
 *
 *       Filename:  2DRainWater.cpp
 *
 *    Description:  
 *
 *    Given a 2D matrix where each element represents the elevation(height) on that point, find how many rain water it is able to hold.
 *
 *    For example, given the below 3×3 matrix:
 *    3 3 3
 *    3 0 3
 *    3 3 3
 *
 *    It should hold 3 units of rain water.
 *
 *    Note: Only the algorithm design part itself is sufficient, no coding is necessary. (You will see why)
 *
 *
 *        Version:  1.0
 *        Created:  2012年08月19日 13时05分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */



#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

vector<vector<bool> > Visited;

int HowMuchCanHold(vector<vector<int> > &M, int i, int j) {
	Visited[i][j] = true;

	if( i == 0 || j == 0 || 
			static_cast<unsigned>(i) == M.size() - 1 || 
			static_cast<unsigned>(j) == M[0].size() - 1 )
	{
		return -1;
	}

	int up = M[i - 1][j], down = M[i + 1][j], left = M[i][j - 1], right = M[i][j + 1];
	int minall = INT_MAX;

	if(!Visited[i - 1][j])
		minall = std::min(minall, up);
	if(!Visited[i + 1][j])
		minall = std::min(minall, down);
	if(!Visited[i][j - 1])
		minall = std::min(minall, left);
	if(!Visited[i][j + 1])
		minall = std::min(minall, right);

	int mij = M[i][j];

	if(minall > mij)
		return minall - mij;
	if(minall < mij)
		return -1;

	int minup = INT_MAX, mindown = INT_MAX, minleft = INT_MAX, minright = INT_MAX;
	minall = INT_MAX;

	if(mij == up && Visited[i - 1][j] == false)
		minup = HowMuchCanHold(M, i - 1, j);
	else
		if(mij != up)
			minup = up - M[i][j];

	if(mij == down && Visited[i+1][j] == false)
		mindown = HowMuchCanHold(M, i + 1, j);
	else
		if(mij != down)
			mindown = down - M[i][j];

	if(mij == left && Visited[i][j - 1] == false)
		minleft = HowMuchCanHold(M, i, j - 1);
	else
		if(mij != left)
			minleft = left - mij;

	if(mij == right && Visited[i][j + 1] == false)
		minright = HowMuchCanHold(M, i, j + 1);
	else
		if(mij != right)
			minright = right - mij;

	minall = std::min(minup, mindown);
	minall = std::min(minall, minleft);
	minall = std::min(minall, minright);

	return minall;
}

void clear_visit() 
{
	for( int i = 0 ; static_cast<unsigned>(i) < Visited.size() ; i++ )
	{
		Visited[i].assign(Visited[i].size(), 0);
	}
}

int solve(vector<vector<int> > &m)
{
	for( int i = 0 ; static_cast<unsigned>(i) < m.size() ; i++ )
	{
		Visited.push_back(vector<bool> ());
		for( int j = 0 ; static_cast<unsigned>(j) < m[i].size() ; j++ )
		{
			Visited[i].push_back(false);
		}
	}

	int water = 0;
	while( true )
	{
		bool find = 0;
		for( int i = 1 ; static_cast<unsigned>(i) < m.size() - 1 ; i++ )
		{
			for( int j = 1 ; static_cast<unsigned>(j) < m[i].size() - 1 ; j++ )
			{
				clear_visit();
				int w = HowMuchCanHold(m, i, j);
				if( w > 0 )
				{
					m[i][j] += w;
					water += w;
					find = true;
				}
			}
		}
		if(!find)
			break;
	}
	return water;
}

int main(int argc, char *argv[])
{
	int a[][4] = {
		{4, 4, 4, 4},
		{4, 3, 3, 4},
		{4, 3, 0, 4},
		{4, 4, 4, 4}
	};
	const int row = 4, column = 4;
	vector<vector<int> > m;

	for( int i = 0 ; i < row ; i++ )
	{
		m.push_back(vector<int>());
		for( int j = 0 ; j < column ; j++ )
		{
			m[i].push_back(a[i][j]);
		}
	}
	std::cout << "totally can hold " << solve(m) << " water\n";
	return 0;
}
