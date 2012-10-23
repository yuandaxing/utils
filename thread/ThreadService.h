#ifndef  _SIMPLETHREAD_H_INC
#define  _SIMPLETHREAD_H_INC

#include <stdlib.h>
#include <pthread.h>
#include <list>
#include <boost/noncopyable.hpp>
#include <sys/types.h>
#include <unistd.h>
#include <Queue.h>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/bind.hpp>

namespace threadSafe{

class SimpleThread: private boost::noncopyable {
	public:
		typedef void* (*fun)(void *);
		explicit SimpleThread(fun ff): f(ff), thread_id(0) { }
		void start() { pthread_create(&thread_id, NULL, f, NULL); }
		void join() const { pthread_join(thread_id, NULL); }

	private:
		fun f;
		pthread_t thread_id;
};


/*-----------------------------------------------------------------------------
 *  we create a  Thread object, and then start the thread, object must still 
 *  alive
 *-----------------------------------------------------------------------------*/
class Thread: private boost::noncopyable {
	public:
		typedef boost::function<void ()> func;
		explicit Thread(const func &ff): f(ff), thread_id(0) {  }
		void start() { pthread_create(&thread_id, NULL, thread_func, this); }
		void join() const { pthread_join(thread_id, NULL); }

	private:
		func f;
		pthread_t thread_id;
		static void*  thread_func(void *t) {
			Thread *thread = static_cast<Thread *>(t);
			thread->f();
		}
};

/*-----------------------------------------------------------------------------
 *  this class is for wrapping your working, the work must create in heap, so the
 *  construct is private,  and the deconstructor is public, and we donnot want 
 *  boost::function to wrap the work, because that will need more copy overhead.
 *-----------------------------------------------------------------------------*/
template <typename T>
class Work: private boost::noncopyable {
	public:
		typedef void (*func)(T &data); 
		T data;
		func f;

		static boost::shared_ptr<Work<T> > getWork(
				const T &data, func f_) {
			return boost::shared_ptr<Work<T> >(new Work(data, f_));
		}
		static boost::shared_ptr<Work<T> > getWork(
				const func &f_) {
			return boost::shared_ptr<Work<T> >(new Work(f_));
		}

	private:
		Work(const T &d, func f_): data(d), f(f_) { }
		explicit Work(func f_): f(f_) { }
};

template <typename T>
class ThreadPoolWorker: private boost::noncopyable {
	private:
		boost::ptr_vector<Thread> threads;
		bool running;
		const int nThread;
		std::list<boost::shared_ptr<Work<T> > > works;
		Mutex m;
		Condition notEmpty;

		void function() {
			while(running) {
				try{ 

					boost::shared_ptr<Work<T> > work ;

					{
						MutexGuard mg(m);

						while(running && works.empty())
							notEmpty.wait();

						if(works.empty())
							continue;

						work = works.front();
						works.pop_front();
					}

					work->f(work->data);
				} catch(...) {
					fprintf(stderr, "some error in ThreadPoolWorker");
				}
			}
		}

	public:
		void putWork(const boost::shared_ptr<Work<T> > &ptr) {
			MutexGuard mg(m);
			works.push_back(ptr);
			notEmpty.notify();
		}

		ThreadPoolWorker(const int &nThread_): 
			nThread(nThread_), running(false), notEmpty(m) { }

		~ThreadPoolWorker() {
			stop();
		}

		void start() {
			{
				MutexGuard mg(m);
				if(running)
					return ;
				running = true;
			}

			for(int i = 0; i < nThread; i++) {
				threads.push_back(new Thread(
							boost::bind(&ThreadPoolWorker::function, this)));
				threads[i].start();
			}
		}

		void join() {
			for(int i = 0; i < nThread; i++)
				threads[i].join();
		}

		void stop() {
			if(running == false)
				return ;

			running = false;
			notEmpty.notifyAll();
			join();
		}

};

namespace ThreadUtils{
	inline pid_t pid() { return getpid();} 
	inline pthread_t thread_id() { return pthread_self(); }
}

}




#endif   /* ----- #ifndef _SIMPLETHREAD_H_INC  ----- */
