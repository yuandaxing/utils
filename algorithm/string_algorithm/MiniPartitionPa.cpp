//to demeonstrate 
#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include "../../Common.h"

bool isP( const char *s, const char *e ) {
	while( s < e ) { 
		if( *s != *e )
			return false;
		s++, e--;
	}
	return true;
}
int minimumPartitionPalindrome( const char *str ) {
	std::string  s(str);
	std::vector<std::vector<int> > mv( 
		s.size(), std::vector<int>( s.size(), 0 ) );

	for( int i = 0; static_cast<unsigned>(i) < s.size(); i++ ) 
		mv[i][i] = 1;

	for( int gap = 1; static_cast<unsigned>(gap) < s.size(); gap++ ) {
		for( int i = 0; static_cast<unsigned>(i) < s.size() - gap; i++ ) {
			if( isP( &s[i], &s[i+gap] ) ) {
				mv[i][i+gap] = 1;
			} else {
				int min = INT_MAX;
				for( int j = i; j < i + gap; j++ ) {
					if( min > mv[i][j] + mv[j+1][i+gap])
						min = mv[i][j] + mv[j+1][i+gap];
				}
				mv[i][i+gap] = min;		
			}
		}
	}


	std::cout << mv << std::endl;

	return mv[0][s.size()-1];
}

int main() {
	const char *str = "abacadacd";
	std::cout << minimumPartitionPalindrome( str );
	return 0;
}
