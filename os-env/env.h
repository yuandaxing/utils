/*
 * =====================================================================================
 *
 *       Filename:  env.h
 *
 *    Description:  to abstract the os environment
 *
 *        Version:  1.0
 *        Created:  2012年06月08日 16时53分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef  _ENV_H_INC
#define  _ENV_H_INC

namespace OS{
class SequentialFile : boost::noncopyable {
	public:
		SequentialFile() { } 
		virtual SequentialFile() { }
		virtual Read(uint64_t size, char *buff) = 0 ;
}
class RandomAccessFile : boost::noncopyable {
	public:
		RandomAccessFile() { }
		virtual ~RandomAccessFile() { }
		virtual uint64_t Read(uint64_t offset, uint64_t size, char *buff) = 0 ;
};
class AppendOnlyFile : boost::noncopyable {
	public:
		AppendOnlyFile() { }
		virtual ~AppendOnlyFile() { }
		virtual uint64_t Append(uint64_t size, char *buff) = 0 ;
		virtual uint64_t Size() = 0 ;
		virtual void Sync() = 0 ;
		virtual void Close() = 0 ;
};
class Socket : boost::noncopyable {
	public:
		enum SocketOpt{
			NONBLOCK = 1,
			REUSEABLE = 2,
			LINGER = 4,

		};
		Socket() { }
		virtual ~Socket() { }
		int Write(uint32_t size, char *buff) = 0 ;
		int Read(uint32_t size, char *buff) = 0 ;
		void SetOpt(enum SocketOpt so) = 0 ;
		void Close() = 0 ;
		Socket * Listen() = 0 ; 
};

class SelectFD : boost::noncopyable {
	public:
		enum Type{
			READ,
			WRITE,
			LISTEN
		};
		SelectFD() { }
		virtual SelectFD() { }
		virtual int Register(const Socket &s, enum Type type) = 0 ;
		virtual int UnRegister(const Socket &s, enum Type type) = 0 ;
};

class Timer : boost::noncopyable {
	public:
		enum Type{
			PERSISTENT,
			NONPERSISTENT
		};
		Timer(uint64_t interval, enum Type t) :
   			interval_(interval), t_(t) { 
			MutexGuard(m_);
			id = last_id_++;
		}
		~Timer() { } 
		
	
	private:
		uint64_t id;
		uint64_t interval_;
		enum Type t_;
		static uint64_t last_id_;
		static Mutex m_;
};


class ENV{
	public:
		ENV() { }
		virtual ~ENV() { }
		virtual AppendOnlyFile * NewAppendOnlyFile(const string &path) = 0 ;
		virtual RandomAccessFile * NewRandomAccessFile(const string &path) = 0 ;
		virtual void DeleteFile(const string &path) = 0 ;
		virtual const string ReadLittleFile(const string &path) = 0 ;
		virtual uint32_t GetNCPU() = 0 ;
		virtual uint32_t GetTotalMem() = 0 ; //M
		virtual list<string> GetChildrenFile(const string &path) = 0 ;
		virtual uint64_t GetMilliSec() = 0 ;
};

extern ENV * NewEnv( ) ;
}
#endif   /* ----- #ifndef _ENV_H_INC  ----- */
