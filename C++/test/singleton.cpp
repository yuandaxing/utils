/*
 * =====================================================================================
 *
 *       Filename:  singleton.cpp
 *
 *    Description:  singleton
 *
 *        Version:  1.0
 *        Created:  2012年04月23日 17时18分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yuan DaXing (http://hi.baidu.com/%E8%A2%81%E5%A4%A7%E6%98%9F/home), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
class singleton{
		private:
				static singleton *instance;
				singleton() {}
				singleton(singleton &);
		public:
				static singleton & getInstance() {
						return *instance;
				}
};
singleton * singleton::instance = new singleton();

class _singleton{
		protected:
				static _singleton *instance;
				_singleton() {}
				_singleton(const _singleton &);
				_singleton & operator=(const _singleton &);
		public:
				static _singleton & getInstance() {
						return *instance;
				}
};
_singleton * _singleton::instance = new _singleton();
		int
main ( int argc, char *argv[] )
{
		singleton &st = singleton::getInstance();
		std::cout << "address:" << &st;
		return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
