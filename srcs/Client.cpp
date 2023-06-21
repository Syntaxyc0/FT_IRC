#include "Client.hpp"

Client::Client(int fd, std::string hostname): _fd(fd), _hostname(hostname)
{
	_is_registered = 0;
}

Client::~Client() {}

//****************************************************//
//                      Setter                        //
//****************************************************//

void	Client::set_fd(int fd)
{
	_fd = fd;
}

void	Client::set_username(std::string username)
{
	_username = username;
}

void	Client::set_hostname(std::string hostname)
{
	_hostname = hostname;
}

void	Client::set_nickname(std::string nickname)
{
	_nickname = nickname;
}

void	Client::set_realname(std::string realname)
{
	_realname = realname;
}

void	Client::set_register(int state)
{
	_is_registered = state;
}

void	Client::set_add_channel(Channel *new_channel)
{
	_channelList.push_back( new_channel->get_name() );
}

//****************************************************//
//                      Getter                        //
//****************************************************//

int	Client::get_fd()
{
	return _fd;
}

std::string	Client::get_username()
{
	return _username;
}

std::string	Client::get_realname()
{
	return _realname;
}

std::string Client::get_hostname()
{
	return _hostname;
}

std::string Client::get_nickname()
{
	return _nickname;
}

int	Client::get_registered()
{
	return _is_registered;
}

std::vector<std::string>	Client::get_channelList()
{
	return _channelList;
}

//****************************************************//
//                     Function                       //
//****************************************************//

void	Client::send_reply(std::string message)
{
	std::string		username;
	std::string		hostname;

	if (!_username.empty())
		username = "!" + _username;
	else
		username = "";
	if (!_hostname.empty())
		hostname = "@" + _hostname;
	else
		hostname = ""; 
		
	std::string 	reply = ":" + _nickname + username + hostname + " " + message + "\r\n";
	if (send(_fd, reply.c_str(), reply.size(), 0) == -1)
		throw	std::runtime_error(strerror(errno));
}

void	Client::send_message(std::string message)
{
	std::string ret(message);
	ret += "\r\n";
	if (send(_fd, ret.c_str(), ret.size(), 0) == -1)
		throw	std::runtime_error(strerror(errno));
}

void	Client::send_privmessage_from(Client *source, std::string message)
{
	std::string ret = "";
	ret += ":" + source->get_fullname() + " PRIVMSG " + _nickname + " :" + message + "\r\n";
	if (send(_fd, ret.c_str(), ret.size(), 0) == -1)
		throw	std::runtime_error(strerror(errno));
}

void	Client::send_message_in_channel(std::string channel, std::string message)
{
	std::string msg = "PRIVMSG " + channel + " :" + message;
	send_message(msg);
}

std::string	Client::get_fullname()
{
	std::string		username;
	std::string		hostname;
	if (!_username.empty())
		username = "!" + _username;
	else
		username = "";
	if (!_hostname.empty())
		hostname = "@" + _hostname;
	else
		hostname = "";
	return (_nickname + username + hostname);
}