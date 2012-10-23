/*
 * =====================================================================================
 *
 *       Filename:  Channel.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月20日 17时32分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

/* 
 * currently Channel do not support timeout
 * */
#ifndef  MESSAGER_CHANNEL_H__INC
#define  MESSAGER_CHANNEL_H__INC
#include <string>
#include <sys/epoll.h>
class Channel {
	public:
		friend class EPoller;
		enum Options {
			kNoBlocking = 1, 
			kNoDelay    = 2, 
			kLinger 	= 4,
			kKeepAlive  = 8, 
			kReuse 		= 16
		};
		enum State {
		   kNew 		= 1, 
		   kAdded 		= 2, 
		   kDelete 		= 4
		};	   
		enum EventType {
			kRead 	= EPOLLPRI|EPOLLIN,
			kWrite 	= EPOLLOUT
		};
		Channel( );
		~Channel( );
		int read(char *buf, int size);
		int write(const char *buf, int size);
		bool connect(const struct sockaddr_in &);
		Channel * accept();
		bool bind(const struct sockaddr_in &);
		bool listen(int qsize);
		bool setOption(int options);
		void close();
		bool Valid();
		bool readable();
		bool writeable();
		bool error();
	private:
		//no copy
		Channel(const Channel&);
		Channel & operator=(const Channel&);

		void setEvent(EventType e) {
			event_ |= e;
		}

		void setWhyWakeup(int w) { whyWakeup_ = w; }
		int fd_;
		int event_;
		int whyWakeup_;
		enum State state_;
		bool Valid_;
};
#endif   /* ----- #ifndef MESSAGER_CHANNEL_H__INC  ----- */
