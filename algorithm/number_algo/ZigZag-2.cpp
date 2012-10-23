#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#define ISSPACE(x) ((x)==' '||(x)=='\r'||(x)=='\n'||(x)=='\f'||(x)=='\b'||(x)=='\t')

char * rightTrim(char *str){
    int len = strlen(str);
    while(--len>=0){
        if(ISSPACE(str[len])){
            str[len] = '\0';
        }else{
            break;
        }
    }
    return str;
}

char * getInputLine(char *buffer, int length){
    if(fgets(buffer,length, stdin)==NULL){
        return NULL;
    }
    rightTrim(buffer);
    if(strlen(buffer)<=0){
        return NULL;
    }
    return buffer;
}

void maxNeighboringPeak(char ** data, int count){
/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	using namespace std;
	bool isFisrt= true;
	for( int i = 0 ; i < count ; i++ )
	{
		istringstream isstr(data[i]);
		vector<int> vector_int;

		while( isstr )
		{
			int kk;
			isstr >> kk;
			vector_int.push_back(kk);
		}

		int first = vector_int[0];
		int last = vector_int[1];
		int max = abs(first - last);
		bool increase = last > first;
		for( int k = 2 ; static_cast<unsigned>(k) < vector_int.size() ;k++)
		{
			if( (increase && vector_int[k]  < last) || 
					(!increase && vector_int[k] > last))
			{
				int curmax = abs(last - first);
				max = std::max(curmax, max);
				first = last;
				last = vector_int[k];
				increase = !increase;
			}
			last = vector_int[k];
		}
		int curmax = abs(last - first);
		max = std::max(curmax, max);

		if( isFisrt)
		{
			cout << max;
			isFisrt= false;
		} else {
			cout << "," << max;
		}
	}
}


int main(int argc, char ** argv){
    char buffers[1024][1024];
    char *input[1024];
    int inputCount = 0;
    while(getInputLine(buffers[inputCount], 1024) != NULL){
        input[inputCount] = buffers[inputCount];
		inputCount++;
    }
    maxNeighboringPeak(input, inputCount);
    return 0;
}
