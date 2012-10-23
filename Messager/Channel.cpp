/*
 * =====================================================================================
 *
 *       Filename:  Channel.cpp
 *
 *    Description:  implement
 *
 *        Version:  1.0
 *        Created:  2012年09月21日 19时17分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Channel.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

Channel::Channel():fd_(-1), event_(0), whyWakeup_(0),
	state_(kNew), Valid_(false) {
		fd_ = socket(AF_INET,SOCK_STREAM 
				| SOCK_CLOEXEC, IPPROTO_TCP);
		Valid_ = (fd_ > 0);
}

Channel::~Channel( ) {
	close();
}

void Channel::close() {
	if( Valid_ )
	{
		::close(fd_);
		Valid_ = false;
	}
}

int Channel::read(char *buf, int size) {
	return ::read(fd_, buf, size);
}

int Channel::write(const char *buf, int size) {
	return ::write(fd_, buf, size);
}
bool Channel::connect(const struct sockaddr_in &sock) {
	return ::connect(fd_, (sockaddr*)&sock, sizeof(sock)) == 0 ;
}
bool Channel::listen(int qsize) {
	return ::listen(fd_, qsize) == 0;
}

bool Channel::readable() {
	return whyWakeup_ & (EPOLLPRI | EPOLLIN);
}
bool Channel::writeable() {
	return whyWakeup_ & EPOLLOUT;
}
bool Channel::error( ) {
	return !readable() && !writeable() ;
}

bool Channel::bind(const struct sockaddr_in &sock) {
	return ::bind(fd_, (const struct sockaddr*)sock, 
			sizeof(sock)) == 0;
}

void Channel::setOption(int options) {
	if(options & kNoBlocking != 0)
		fcntl(
}
}
}


