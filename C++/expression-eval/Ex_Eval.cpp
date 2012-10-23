/*
 * =====================================================================================
 *
 *       Filename:  Ex_Eval.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月25日 21时22分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <assert.h>
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <string>
class Op {
	private:
		enum { len_ = 7, ND = 1000 };
		static const char ops_[len_];
		static const int priority_[len_][len_];
	public:
		static int pri( char left, char right ) {
			int lidx = std::find( ops_, ops_+len_, left ) - ops_;
			int ridx = std::find( ops_, ops_+len_, right ) - ops_;
			return priority_[ridx][lidx];
		}
};

const char Op::ops_[len_] = { '#', '+', '-', '*', '/', '(', ')'};
//1 mean we must push the operator into the stack because it's higher priority
//-1 mean we can compute the last operator
const int Op::priority_[len_][len_] = {
	{0, -1, -1, -1, -1, -1, -1},
	{1, -1, -1, -1, -1,  1, -1},
	{1, -1, -1, -1, -1,  1, -1},
	{1,  1,  1, -1, -1,  1, -1},
	{1,  1,  1, -1, -1,  1, -1},
	{1,  1,  1,  1,  1,  1, -1},
	{-1,-1, -1, -1, -1,  0, -1}
};

int find_not_digit(const std::string &str, int start) {
	return str.find_first_not_of("0123456789", start);
}
int eval(int left, int right, char op) {
	switch ( op )
	{
		case '+' :
			return left + right;
		case '-' :
			return left - right;
		case '*' :
			return left * right;
		case '/' :
			return left / right;
	}
	return 0;
}
int expressionEvaluate( const std::string &str1 ) {

	std::stack<char> op;
	std::stack<int> oprand;
	op.push('#');
	std::string str(str1);
	str.push_back('#');

	int start = 0;
	//actually we would like to deal operator and operand the same
	while(static_cast<std::string::size_type>(start)
			!= std::string::npos) {
		if( isdigit(str[start]) )
		{
			int v = atoi(&str[start]);
			oprand.push(v);
			start = find_not_digit(str, start);
		} else {
			int priority = Op::pri(op.top(), str[start]);
			int left, right;
			char oper;
			switch ( priority )
			{
				//we cannot define variable in case 
				case -1: 
					right = oprand.top(); 
					oprand.pop();
					left = oprand.top(); 
					oprand.pop();
					oper = op.top(); 
					op.pop();
					oprand.push(eval(left, right, oper));
					break;
				case 0:
					op.pop();
					start = str.find_first_not_of("\t\n\r ", start+1);
					break;
				case 1:
					op.push(str[start]);
					start = str.find_first_not_of("\t\n\r ", start+1);
					break;
				default :
					break;
			}
		}
	}
	if(oprand.empty())
		return 0;
	return oprand.top();
}

void preProcess(std::string &s) {
	int start = s.find_first_of("(");
	while(static_cast<std::string::size_type>(start) != std::string::npos) {
		if(start != 0 && isdigit(s[start-1])) {
			s.insert(start, 1, '*');
			start++;
		}
		start = s.find_first_of("(", start+1); 
	}
	start = s.find_first_of(")");
	while(static_cast<std::string::size_type>(start) != std::string::npos) {
		if(static_cast<std::string::size_type>(start) != s.size() 
				&& isdigit(s[start+1])) {
			s.insert(start+1, 1, '*');
			start++;
		}
		start = s.find_first_of(")", start+1); 
	}
}
int main(int argc, char *argv[])
{
	std::string str="11+3*((22+4))/4+4";
	std::string str2 = "11*3*(2+4)/3";
	std::string str3 = "11-3*(2+4)/3";
	std::string str4 = "11-3((2+4)3)3";
	preProcess(str4);
	std::cout << str4 << std::endl;
	std::cout << expressionEvaluate(str) << std::endl;
	assert(expressionEvaluate(str2) == 66);
	assert(expressionEvaluate(str3) == 5);
	std::cout << str4 << ":" << expressionEvaluate(str4) << std::endl;
	return 0;
}
