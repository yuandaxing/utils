/*
 * =====================================================================================
 *
 *       Filename:  SimplePingPong.h
 *
 *    Description:  pingpingServer.h
 *
 *        Version:  1.0
 *        Created:  2012年12月08日 14时57分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string>
#include <vector>
#include "Channel.h"
#include "EventLoop.h"
#include <algorithm>
class PingPongClient {
	public:
		PingPongClient(Channel *ch) : ch_(ch) {
		}
		~PingPongClient() { delete ch_; }
		void read_handler(EventLoop *el, Channel *);
		void write_handler(EventLoop *el, Channel *);
		void err_handler(EventLoop *el, Channel *);
	private:
		std::vector<char> buffer_;
		Channel *ch_;
};

void PingPongClient::read_handler(EventLoop *el, Channel *ch) {
	unsigned pos = buffer_.size();
	unsigned rbyte = 0;
	while(rbyte != 1024) {
		buffer_.resize(pos + 1024);
		rbyte = ch->read(buffer_.data() + pos, 1024);
		pos += rbyte;
		buffer_.resize(pos);
	}

	//currently we just remove the channle
	ch_->unregEventLoop(el, Channel::EventType::kRead);
	ch_->regEventLoop(el, Channel::EventType::kWrite);
}	

void PingPongClient::write_handler(EventLoop *el, Channel *ch) {
	while(buffer_.size() > 0) {
		unsigned wbyte = ch->write(buffer_.data(), buffer_.size());
		if( wbyte > 0 )
		{
			std::copy(buffer_.begin() + wbyte, buffer_.end(),
					buffer_.begin());
		} else if( wbyte == 0 )
		{
			//error handling
			break;
		} else {
			break;
		}
	}

	if( buffer_.size() == 0 )
	{
		ch_->unregEventLoop(el, Channel::EventType::kWrite);
		ch_->regEventLoop(el, Channel::EventType::kRead);	
	}
}

class PingPongServer {
	public:
		PingPongServer(const std::string &address, int port);
		void ListeningHandler(Channel *);
		void server() {
			el_.loop();
		}

	private:
		std::vector<PingPongClient *> clients_;
		Channel listen_ch_;
		EventLoop el_;
		std::string address_;
		int port_;
};

