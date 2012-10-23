#include <ThreadService.h>
#include <LockService.h>
#include <queue>
#include <boost/ptr_container/ptr_vector.hpp>

std::queue<int> Q;
threadSafe::Mutex m;
const int nThread = 10;
const int nNum = 10000;
void* f(void *) {
	for(int i = 0; i < nNum; i++) {
		threadSafe::MutexGuard mg(m);
		Q.push(i);
	}
}

using threadSafe::Mutex;
using threadSafe::Condition;
using threadSafe::MutexGuard;
Mutex& getMutex() {
	static Mutex m;
	return m;
}

Condition & getCondtionFull(Mutex &m) {
	static Condition cond(m);
	return cond;
}

Condition & getCondtionEmpty(Mutex &m) {
	static Condition cond(m);
	return cond;
}

int Qi = 0;
bool has = false;
void * f1(void *) {
	Mutex &m = getMutex();
	Condition &c1 = getCondtionFull(m), &c2 = getCondtionEmpty(m);
	for(int i = 0; i < nNum; i++) {
		MutexGuard mg(m);
		while(has == true)
			c2.wait();
		Qi = i;
		has = true;
		c1.notify();
	}
}	

void* f2(void *) {
	Mutex &m = getMutex();
	Condition &c1 = getCondtionFull(m), &c2 = getCondtionEmpty(m);
	for(int i = 0; i < nNum; i++) {
		MutexGuard mg(m);
		while(has == false)
			c1.wait();
		int z = Qi;
		has = false;
		assert(z == i);
		c2.notify();
	}
}
int main()
{
	using threadSafe::SimpleThread;
	boost::ptr_vector<SimpleThread> threads;
	for(int i = 0; i < nThread; i++) {
		threads.push_back(new SimpleThread(f));
		threads.back().start();
	}

	for(int i = 0; i < nThread; i++) {
		threads[i].join();
	}
	
	assert(Q.size() == nNum * nThread);
	printf("Mutex and MutexGuard is OK\n");

	SimpleThread st1(f1), st2(f2);
	st1.start(); 
	st2.start();

	st1.join();
	st2.join();
	printf("Condtion is Ok\n");
	return 0;
}
