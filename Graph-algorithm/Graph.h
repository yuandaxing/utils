/*
 * =====================================================================================
 *
 *       Filename:  GraphCreator.cpp
 *
 *    Description:  this File provide the graph creator, one to create a graph from a matrix, the other is to creat from adjcent list.
 *    first we need to read the file, return the Graph.
 *
 *        Version:  1.0
 *        Created:  2012年09月06日 16时23分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef  GRAPHCREATOR_H__INC
#define  GRAPHCREATOR_H__INC

#include <iostream>
#include <assert.h>
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
/* 
 * the Graph format in file is
 * 1         N: the number of vectices
 * 2         A B C :the name of the  vertice are  A, B, C
 * 3         1 1 :the weight between vertice A and B is 1 
 * 4         2 4 :the weight between vertice B and C is 4 
 * 5         0 1 1 1:the weight between vertice C and B, C and A is 1
 *
 */
const int MaxDistance = 10000;
typedef std::pair<int, int> edge;
typedef std::vector<std::vector<edge> > adjList;
class MatrixGraph {
	public:
		char getVerticeName(int idx) const ;
		// this get and set maybe not that easy to use
		int  getWeight(int idx1, int idx2) const ;
		void setWeight(int idx1, int idx2, int w) ;
		void transpose( );

		// override operator[] for more easy usage
		std::vector<int>& operator[] ( int idx ) {
			return matrix_[idx] ;
		}

		const std::vector<int>& operator[] ( int idx ) const {
			return matrix_[idx] ;
		}

		int  getSize() const ;
		explicit MatrixGraph(const std::string &s) ;
		MatrixGraph(int N);

		//we should allow copy constructor, but not copy assignment
	private:
		//MatrixGraph& operator=(const MatrixGraph& ) ;

		std::vector<char>  name_;
		std::vector<std::vector<int> > matrix_;

		//this may be not that nesscery
		int nameIdx(char c) {
			return std::find(name_.begin(), name_.end(), c) - name_.begin();
		}
};

void MatrixGraph::transpose( ) {
	for( int i = 0 ; i < getSize() ; i++ )
	{
		for( int j = i + 1 ; j < getSize() ; j++ )
		{
			std::swap(matrix_[i][j], matrix_[j][i]);
		}
		
	}
}
std::ostream& operator<<( std::ostream &out, 
		const MatrixGraph &mg ) {
	for( int i = 0 ; i < mg.getSize() ; i++ )
	{
		out << mg.getVerticeName(i) << " " ;
	}

	out << std::endl;

	for( int i = 0 ; i < mg.getSize() ; i++ )
	{
		for( int j = 0 ; j < mg.getSize() ; j++ )
		{
			out << mg[i][j] << " " ;
		}
		out << std::endl;
	}

	out << std::endl;
	return out;	
}
char MatrixGraph::getVerticeName(int idx) const {
	return name_[idx];
}
int MatrixGraph::getWeight(int idx1, int idx2) const {
	return matrix_[idx1][idx2];
}

void MatrixGraph::setWeight(int idx1, int idx2, int w) {
	matrix_[idx1][idx2] = w;
}

int MatrixGraph::getSize() const {
	return matrix_.size();
}
bool isName(char c) {
	return (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ;
}

namespace Helper { 
void getNameHelper(std::ifstream &fin, std::vector<char> &vname) {
	const int maxChar = 1000;
	char name[maxChar] = {0};
	//here we use string to process, maybe it is easy
	fin.getline(name, maxChar);

	char *p = std::find_if(name, name+maxChar, isName);
	for( ; p < name + maxChar ; p = std::find_if(p + 1, name + maxChar, isName) )
	{
		vname.push_back(*p);
	}
}

adjList getEdgeHelper(std::ifstream &fin, int N) {
	adjList adj;
	for( int i = 0 ; i < N ; i++ )
	{
		adj.push_back( std::vector<edge>() );
		std::string line;
		getline(fin, line);
		
		size_t pos = line.find_first_not_of(" \t\n");

		while( pos != std::string::npos )
		{
			int idx, value;
			edge e;
			idx = atoi( &line[pos] );
			pos = line.find_first_of( "\t\n ", pos+1);
			pos = line.find_first_not_of("\t\n ", pos+1);
			value = atoi(&line[pos]);
			pos = line.find_first_of("\t\n ", pos);
			pos = line.find_first_not_of("\t\n ", pos);
			e.first = idx;
			e.second = value;
			adj[i].push_back(e);
		}
	}

	return adj;
}
}

MatrixGraph::MatrixGraph(int N) {
	for( int i = 0 ; i < N ; i++ )
	{
		matrix_.push_back( std::vector<int>() );
		matrix_[i].assign( N, MaxDistance );
		matrix_[i][i] = 0;
	}
}
MatrixGraph::MatrixGraph(const std::string &s) {
	std::ifstream fin(s.c_str());
	
	if( !fin )
	{
		std::cout << "could not open the file\n";
		exit(0);
	}
	
	int N;
	fin >> N;
	const int max = 1000;
	char trail[max];
	fin.getline(trail, max);

	for( int i = 0 ; i < N ; i++ )
	{
		matrix_.push_back(std::vector<int>());
		matrix_[i].assign(N, MaxDistance);
		matrix_[i][i] = 0;
	}

	Helper::getNameHelper(fin, name_);
	assert(name_.size() == static_cast<unsigned>(N) );
	adjList adj = Helper::getEdgeHelper(fin, N);

	int row = 0;
	for( adjList::iterator iter = adj.begin() ; 
			iter != adj.end() ; iter++ )
	{
		for( std::vector<edge>::iterator eiter = iter->begin() ;
			   	eiter != iter->end() ; eiter++ )
		{
			setWeight(row, eiter->first, eiter->second);
		}
		row++;
	}
}

class AdjacentGraph {
	public:
		char getVerticeName(int idx) const;
		const std::vector<edge>& getAdjacentRef(int idx) const;
		//for easy access, also override operator[]

		std::vector<edge>& operator[]( int idx ) {
			return adj_[idx];
		}

		const std::vector<edge>& operator[] ( int idx ) const {
			return adj_[idx];
		}

		int getSize() const ;
		AdjacentGraph(const std::string &);
		AdjacentGraph(int N);
		void transpose( );
	private:
		// do not allow copy assignment
		AdjacentGraph& operator=(const AdjacentGraph& );
		std::vector<char> name_;
		adjList adj_;
};

void AdjacentGraph::transpose() {
	adjList tmp(getSize(), std::vector<edge>() );
	for( int i = 0 ; i < getSize() ; i++ )
	{
		for( int j = 0 ; static_cast<unsigned>(j) < adj_[i].size() ; j++ )
		{
			edge e = adj_[i][j];
			tmp[e.first].push_back(std::make_pair(i, e.second) );
		}
	}

	for( int i = 0 ; static_cast<unsigned>(i) < tmp.size() ; i++ )
	{
		std::sort(tmp[i].begin(), tmp[i].end());
	}
	
	adj_ = tmp;
}
std::ostream& operator<<(std::ostream& out, const AdjacentGraph& adjG) {
	for( int i = 0 ; i < adjG.getSize() ; i++ )
	{
		out << adjG.getVerticeName(i) << " ";
	}
	out << std::endl;

	for( int i = 0 ; i < adjG.getSize() ; i++ )
	{
		for( int j = 0 ; static_cast<unsigned>(j) < adjG[i].size() ; j++ )
		{
			out << adjG[i][j].first << " " << adjG[i][j].second << "\t";
		}
		out << std::endl;
	}
	out << std::endl;
	return out;
}
char AdjacentGraph::getVerticeName(int idx) const {
	return name_[idx];
}
const std::vector<edge>& AdjacentGraph::getAdjacentRef(int idx) const {
	return adj_[idx];
}

int AdjacentGraph::getSize() const {
	return adj_.size();
}

AdjacentGraph::AdjacentGraph(int N) : adj_(N, std::vector<edge>()){
	
}
AdjacentGraph::AdjacentGraph(const std::string &str) {

	std::ifstream fin(str.c_str());
	
	if( !fin )
	{
		std::cout << "could not open the file\n";
		exit(0);
	}
	
	int N;
	fin >> N;

	const int max = 1000;
	char trail[max];
	fin.getline(trail, max);

	Helper::getNameHelper(fin, name_);
	assert( name_.size() == static_cast<unsigned>(N) );
	adj_ = Helper::getEdgeHelper(fin, N);
}
#endif   /* ----- #ifndef GRAPHCREATOR_H__INC  ----- */
