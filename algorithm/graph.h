/*
 * =====================================================================================
 *
 *       Filename:  graph.h
 *
 *    Description:  a graph imeplemtation
 *
 *        Version:  1.0
 *        Created:  2012年07月01日 19时09分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef  GRAPH_H_INC
#define  GRAPH_H_INC

#include <vector>
#include <tr1/memory>
#include <map>
namespace utils{
template <typename T>
struct Node{
	std::vector<Node *> neighbors;
	T data;
};
template <typename T>
class GraphCreator{
	public:
		typedef Node<T> * Graph;
		typedef Node<T> * Node_ptr;
		GraphCreator() : head_(NULL) {}
		//first add a node the pre is NULL;
		void addNode(Node_ptr pre, Node_ptr cur);
	private:
		Graph *head_;
		std::map<Node_ptr> 
		//no copy
		Graph(const Graph &);
		Graph & operator=(const Graph &);
};
}
#endif   /* ----- #ifndef GRAPH_H_INC  ----- */
