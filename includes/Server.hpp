#ifndef	SERVER_HPP
# define SERVER_HPP

// # include "Channel.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include <sstream>
#include <iostream>
#include <cstring>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/poll.h>
#include <errno.h>
#include <list>
#include "Color.h"
#include "Commands.hpp"
#include <map>

class	Client;
void errorin(int err, const std::string msg);

class Server
{
    private:
        const char					*_port;
        const char					*_password;
		std::map<int, Client *>		_clientList;
		std::vector<pollfd>			_sockets;
		int 						_listening_socket;

        int				flags;
        struct pollfd	sockets[SOMAXCONN + 1]; //listening socket is sockets[0]
        int	socket_number;
        int	events_number;
		int				_exit;
        void			init_server();
        int				new_connection();
		void			disconnect(int fd);
	
    public:

        Server();
        ~Server();
        Server &operator=(Server const &a);
        Server(const char *port, const char *password);
        void monitoring();
        int shut_down();

		Client	*find_user_by_nickname(std::string nickname);
		void	adduser(int *fd, std::string hostname);
		void    Pass(Client *client, std::vector<std::string> args);
		void	nick(Client *client, std::vector<std::string> args);
};

// class	Server
// {
// 	private:
// 			std::string					_password;
// 			std::string					_hostname;
// 			int							_port;
// 			std::map<int, Client *>		_clientList;
// 			Channel						*_channels;

// 	public:

// 			Server(int port, std::string password);
// 			~Server();
// };

#endif