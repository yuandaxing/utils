#include <vector>
#include <iostream>

bool isSquare(int num) {
     if(num < 0)
            return false;
     int low = 0, high = num;
     while(low <= high) {
               int mid = (low + high) >> 1;
               int square = mid * mid;
               if(square == num)
                        return true;
               else if(square < num)
                      low = mid + 1;
                    else
                       high = mid - 1;
     }
     return false;
}
int main()
{
    std::vector<int> vi;
    const int size = 100;
    for(int i = 0; i < size; i++) {
            std::cout << i << " " << isSquare(i) << "\t";
    }
    
    getchar();
    return 0;
}
