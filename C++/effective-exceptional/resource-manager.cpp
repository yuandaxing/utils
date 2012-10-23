/*
 * =====================================================================================
 *
 *       Filename:  resource-manager.cpp
 *
 *    Description:  to show how to manager resource
 *
 *        Version:  1.0
 *        Created:  2012年05月03日 08时18分33秒
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
#include <tr1/memory>
#include <memory>
#include <pthread.h>
//boost::scoped_array, boost::shared_array
class Resource{
	private:
		int i, j;
	public:
		Resource(int i1 = 10, int i2 = 20)
			: i(i1), j(i2) { }
		virtual ~Resource() { std::cout << "Resource\n"; }
		Resource(const Resource & r)
			: i(r.i), j(r.j) { }

};
class derived: public Resource{
	public:
		~derived() { std::cout << "derived\n"; }

};

class Uncopyable{
	private:
		Uncopyable(const Uncopyable & u);
		Uncopyable & operator=(const Uncopyable &u);
	public:
		Uncopyable() { }
		~Uncopyable() { }
};

//RAII.  share_pointer is the only way to share resource between multi-thread
class Lock: private Uncopyable{
	public:
		Lock(pthread_mutex_t *m): pm(m) { pthread_mutex_lock(pm); }
		~Lock() { pthread_mutex_unlock(pm); }
	private:
		pthread_mutex_t *pm;
};

int main() {
	//RSCP
	std::tr1::shared_ptr<Resource> pr(new derived);

	Resource *pd = new derived;
	std::auto_ptr<Resource> apr(new derived);

	delete pd;

	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

	{
		Lock l(&lock);
		std::cout << "we are in the lock now\n";
	}

	std::cout << std::endl;
	return 0;
}

