/*
 * =====================================================================================
 *
 *       Filename:  shortest_move.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年07月03日 21时00分09秒
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
#include <bitset>
#include <stack>
#include <tr1/unordered_map>
#include <queue>
#include <algorithm>


const int step_type = 8;
int move_type[step_type][2] = {
	{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
	{2, 1}, {2, -1}, {-2, 1}, {-2, -1}
};

struct Position{
	Position(int x, int y) :
		x_(x), y_(y) { }
	int x_, y_;
};

bool operator==(const Position &lhs, const Position &rhs) {
	return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_;
}
Position next_Position(const Position &p, int x, int y) {
	return Position(p.x_ + x, p.y_ + y);
}
class ChessBoard {
	public:
		ChessBoard(const int size);
		ChessBoard(const int row, const int column);
		bool could_goto(const Position &init, const Position &end, std::vector<Position> &path, const int );
		bool could_goto_best(const Position &init, const Position &end, std::vector<Position> &path );

	private:
		class PositionHasher {
			public:
				PositionHasher(const int row, const int column) :
					row_(row), column_(column) { }

				unsigned int operator( ) (const Position &p) const {
					return p.x_ * row_ + p.y_;
				}	
			private:
				const int row_, column_;
		};
		void cotor_helper() {
			int i;
			for ( i = 0; i <= max_row_; i += 1 ) {
				bit_mark_.push_back(std::vector<char>());
				int j = 0;
				for ( j = 0; j <= max_column_; j += 1 ) {
					bit_mark_[i].push_back(0);
				}
			}
		}

		void reset() {
			int i = 0;
			for ( i = 0; i <= max_row_; i += 1 ) {
				bit_mark_[i].assign(max_column_ + 1, 0);
			}
		}

		bool isPositionValid(const Position &p) {
			return p.x_ > 0 && p.x_ <= max_row_ &&
				p.y_ > 0 && p.y_ <= max_column_;
		}

		bool isMark(const Position &p) {
			return bit_mark_[p.x_][p.y_] > 0;
		}

		void setMark(const Position &p) {
			bit_mark_[p.x_][p.y_] = 1;
		}

		bool auxilary_move(const Position &end, std::vector<Position> &stack, int start, const int maxstep);
		const int max_row_, max_column_;
		std::vector<std::vector<char> > bit_mark_;
		std::tr1::unordered_map<Position, int, PositionHasher> step_cache;

};
ChessBoard::ChessBoard(const int size) :
	max_row_(size), max_column_(size), 
	step_cache(0, PositionHasher(max_row_, max_column_)) {
		cotor_helper();
}

ChessBoard::ChessBoard(const int row, const int column) :
	max_row_(row), max_column_(column), 
	step_cache(0, PositionHasher(max_row_, max_column_)) {
		cotor_helper();
	}

bool ChessBoard::could_goto(const Position &init, const Position &end, std::vector<Position> &path, const int maxstep) {
	if(!isPositionValid(init) || !isPositionValid(end))
		return false;
		
	std::vector<Position> stack;
	stack.push_back(init);
	bool succeed = auxilary_move(end, stack, 0, maxstep);
	reset();
	if(succeed) path = stack;
	return succeed;
}

bool ChessBoard::could_goto_best(const Position &init, const Position &end, 
		std::vector<Position> &path) {

	std::tr1::unordered_map<Position, int, PositionHasher> least_step( 0,
		   	PositionHasher(max_row_, max_column_) );
	std::queue<std::pair<Position, int> > queue;

	queue.push(std::make_pair(init, 0));
	least_step[init] = 0;
	bool goto_end = false;
	while ( !queue.empty() ) {
		//pop the first 
		Position cur = queue.front().first;
		int step = queue.front().second;
		queue.pop();
		for ( int i = 0; i < step_type; i += 1 ) {
			Position next = next_Position(cur, move_type[i][0], move_type[i][1]);
			if ( isPositionValid(next) && least_step.find(next) 
			  		== least_step.end() ) {
				least_step[next] = step + 1;
				queue.push( std::make_pair(next, step + 1) ) ;
				if ( next == end ) {
					goto_end = true;
					break;
				}
			}
		}
		if( goto_end )
			break;
	}

	
	//search back ;
	if ( goto_end ) {
		Position cur = end ;
		int step = least_step[cur] ;
		path.push_back(cur) ;
		while ( true ) {
			if(step == 0)
				break ;
			for ( int i = 0; i < step_type; i += 1 ) {
				Position next = next_Position(cur, move_type[i][0], move_type[i][1]);
				if ( least_step.find(next) != least_step.end() &&
				  least_step[next] == step - 1 ) {
					path.push_back(next);
					cur = next;
					step = step - 1 ;
					break ;
				}
			}

		}
		std::reverse(path.begin(), path.end());
	}
	return goto_end;
}

bool ChessBoard::auxilary_move(const Position &end, std::vector<Position> &stack, int start, int maxstep) {
	Position p = stack[start];
	if(start == maxstep) {
		if ( p == end ) {
			return true;
		}
		else {
			return false;
		}
	}

	
	int i = 0;
	for ( i = 0; i < step_type; i += 1 ) {
		Position next = next_Position(p, move_type[i][0], move_type[i][1]);
		
		if ( isPositionValid(next)  ) {
			stack.push_back(next);
			if ( auxilary_move(end, stack, start + 1, maxstep) ) {
				return true;
			}
			stack.pop_back();	
		}
		else {
			continue;
		}
	}
	return false;
}

bool searchShortestPath(const Position &start, const Position &end, std::vector<Position> &vp) {
	int max_x = std::max(start.x_, end.x_);
	int max_y = std::max(start.y_, end.y_);

	ChessBoard cb(max_x, max_y);
	return cb.could_goto_best(start, end, vp ) ;
	int i = 0;
	for ( i = 1; i <= max_x*max_y; i += 1 ) {
		if ( cb.could_goto(start, end, vp, i)) {
			return true;
		}
	}
	return false;
}	
void print_vp(const std::vector<Position> &vp) {

	for ( std::vector<Position>::const_iterator iter= vp.begin(); 
			iter != vp.end(); iter += 1 ) {
		printf("(%d, %d)  ", iter->x_, iter->y_);
	}
	printf("\n");
}
int main ( int argc, char *argv[] )
{
	const Position start1(1, 1), end1(20, 20);
	std::vector<Position> vp;
	
	if ( searchShortestPath(start1, end1, vp) ) {
		print_vp(vp);
	}
	return 0;
}				/* ----------  end of function main  ---------- */
