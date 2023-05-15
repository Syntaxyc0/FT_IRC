#ifndef	SERVER_HPP
# define SERVER_HPP

// # include "Channel.hpp"
#include "Client.hpp"
#include "Replies.hpp"
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
		// std::list<Client*>			_userlist;
        const char					*_port;
        const char					*_password;
		std::map<int, Client *>		_clientList;
		std::vector<pollfd>			_sockets;



        int				flags;
        struct pollfd	sockets[SOMAXCONN + 1]; //listening socket is sockets[0]
        int	socket_number;
        int	events_number;
		int				_exit;
        void			init_server();
        int				new_connection();
	
    public:

        Server();
        ~Server();
        Server &operator=(Server const &a);
        Server(const char *port, const char *password);
        void monitoring();
        int shut_down();

		void	adduser(int fd, std::string hostname);
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