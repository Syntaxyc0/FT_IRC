#ifndef	CLIENT_HPP
# define CLIENT_HPP

# include <sys/socket.h>
# include <string>
# include <iostream>
# include <sstream>
# include <vector>
# include "Channel.hpp"

class	Client
{
	private:
			int _fd;
			std::string	_hostname;
			std::string	_username;
			std::string	_realname;
			std::string	_nickname;

			bool		_is_registered;
			Channel		_current_channel;

	public:

			Client(int fd, std::string hostname);
			~Client();

		// Setters
			void	set_fd(int fd);
			void	set_register(bool state);
			void	set_hostname(std::string name);
			void	set_username(std::string name);
			void	set_realname(std::string name);
			void	set_nickname(std::string name);

		// Getters
			int				get_fd();
			bool			get_registered();
			std::string		get_hostname();
			std::string		get_username();
			std::string		get_realname();
			std::string		get_nickname();

		// Functions

		
};

#endif