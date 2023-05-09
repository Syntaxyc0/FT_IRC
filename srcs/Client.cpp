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

void	Client::set_register(bool state)
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

bool	Client::get_registered()
{
	return _is_registered;
}