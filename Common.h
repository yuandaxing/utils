/*
 * =====================================================================================
 *
 *       Filename:  Common.h
 *
 *    Description:  for output
 *
 *        Version:  1.0
 *        Created:  2012年09月18日 10时11分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  COMMON_H__INC
#define  COMMON_H__INC
#include <iostream>
#include <vector>
#include <list>
#include <stdint.h>
#include <set>
#include <map>
#include <tr1/unordered_map>

template <typename T, typename V>
std::ostream & operator<<(std::ostream &os, 
		const std::pair<T, V> &pair) {
	return std::cout << "(" << pair.first << "," << pair.second
		<< ")";
}
 
template <typename iterType>
std::ostream & printLine(std::ostream &os, 
		iterType beg, iterType end) {
	while( beg != end )
	{
		os << *beg << " ";
		++beg;
	}
	os << std::endl;
	return os;
}

template <typename T>
std::ostream & operator<<(std::ostream &os, std::vector<T> &vi) {
	return printLine(os, vi.begin(), vi.end());
}

template <typename T>
std::ostream & operator<<(std::ostream &os, std::list<T> &list) {
	return  printLine(os, list.begin(), list.end());
}

template <typename T>
std::ostream & operator<<(std::ostream &os, const std::set<T> &s) {
	return printLine(os, s.begin(), s.end());
}

template <typename T, typename V>
std::ostream & operator<<(std::ostream &os, const std::map<T, V> &map) {
	return printLine(os, map.begin(), map.end());
}
template <typename T, typename V>
std::ostream & operator<<(std::ostream &os, 
		const std::tr1::unordered_map<T, V> &map) {
	return printLine(os, map.begin(), map.end());
}
/* 
template <typename ContainerType>
std::ostream & operator<<(std::ostream &os, ContainerType c) {
	typename ContainerType::iterator iter = c.begin();
	while(iter != c.end()){
		os << *iter << " ";
		++iter;
	}
	return os;
}*/
#endif   /* ----- #ifndef COMMON_H__INC  ----- */
