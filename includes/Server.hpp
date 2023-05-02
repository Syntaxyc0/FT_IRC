#ifndef	SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include <map>
# include <poll.h>


class	Server
{
	private:
			std::string					_password;
			std::string					_hostname;
			int							_port;
			std::map<int, Client *>		_clientList;
			Channel						*_channels;

	public:

			Server(int port, std::string password);
			~Server();
};

#endif