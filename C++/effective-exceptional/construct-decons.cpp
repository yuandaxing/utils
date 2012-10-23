/*
 * =====================================================================================
 *
 *       Filename:  construct-decons.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年05月02日 15时50分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yuan DaXing (http://hi.baidu.com/%E8%A2%81%E5%A4%A7%E6%98%9F/home), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <stdlib.h>
#include <memory>
#include <tr1/memory>
#include <new>

class Empty{
	public:
		Empty() { }
		~Empty() { }
		friend std::ostream & operator<<(std::ostream &out, 
				const Empty & e) {
			out << "Empty\n";
			return out;
		}
	private:
		Empty(const Empty &rhs);
		Empty & operator=(const Empty &rhs);
};

class Uncopyable {
	private:
		Uncopyable(const Uncopyable &rhs);
		Uncopyable & operator=(const Uncopyable &rhs);
	public:
		Uncopyable() {}	
		~Uncopyable() {}
};
class test: private Uncopyable {

};

class TimeKeeper {
	//never call virtual function in constructor or deconstructor
	virtual void init() {
		std::cout << "init TimeKeeper\n";
	}
	public:
		TimeKeeper() { init();std::cout << "con TimeKeeper\n"; }
	/*  	virtual */ ~TimeKeeper() { std::cout << "dec TimeKeeper\n"; }
};


class AtomicClock: public TimeKeeper {
	void init() {
		std::cout << "init AtomicClock\n";
	}
	public:
		AtomicClock() { std::cout << "con AtomicClock\n"; }
		~AtomicClock() { std::cout << "dec AtomicClock\n"; 
					//throw std::bad_alloc();
		}
};

//inherientance the stl class , eg, string, because there deconstructor is not virtual


int main()
{
	Empty e;
	Empty e1;
	//e = e1;
	std::cout << e;

	test t1, t2;
	//t1 = t2;
	//test t3(t1);

//	AtomicClock ac;
	std::tr1::shared_ptr<TimeKeeper> spac(new AtomicClock);

	//TimeKeeper *acp = new AtomicClock();
	//delete acp;

	
	return 0;
}
