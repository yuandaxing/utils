/*
 * =====================================================================================
 *
 *       Filename:  testSharedPtr.cpp
 *
 *    Description:  test
 *
 *        Version:  1.0
 *        Created:  2012年09月16日 18时24分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <boost/make_shared.hpp> 
#include <string>
#include <vector>
int main(int argc, char *argv[])
{

	boost::shared_ptr<std::string> ptrStr = 
		boost::make_shared<std::string>("sssssssss");
	std::cout << *ptrStr << std::endl;


	//it is said that this is more efficient
	std::string *str = new std::string(10, 's');
	boost::shared_ptr<std::string> sharedString(str);
	std::cout << *(ptrStr.get()) << std::endl;

	boost::shared_ptr<std::vector<int> > ptrVec = 
		boost::make_shared<std::vector<int> >(10, 2);

	std::cout << ptrVec->size() << std::endl;
	return 0;
}
