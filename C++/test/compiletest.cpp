#include <iosfwd>
//accelerat the compile time
class test{
	private:
	int i, j, k;
};
std::ostream& operator<<( std::ostream &out , const test &);
int main()
{
	return 0;

}

