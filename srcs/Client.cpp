#include "Client.hpp"

Client::Client(int fd, std::string hostname): _fd(fd), _hostname(hostname)
{
	_is_registered = 0;
}

Client::~Client()
{
}

	// Setters

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

	// Getters

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

void	Client::send_reply(std::string message)
{
	std::string		username;
	std::string		hostname;
	if (_username.empty())
		username = "!" + _username;
	else
		username = "";
	if (_hostname.empty())
		hostname = "@" + _hostname;
	else
		hostname = ""; 
	std::string 	reply = ":" + _nickname + username + hostname + " " + message + "\r\n";
	if (send(_fd, reply.c_str(), reply.size(), 0) == -1)
		throw	std::runtime_error(strerror(errno));
}