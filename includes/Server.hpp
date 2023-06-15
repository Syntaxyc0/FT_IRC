#ifndef	SERVER_HPP
# define SERVER_HPP

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
#include <signal.h>

extern int				 exit_state;

class	Client;
class   Channel;

class Server
{
    private:
        const char					*_port;
        const char					*_password;
		std::map<int, Client *>		_clientList;
		std::vector<pollfd>			_sockets;
		int 						_listening_socket;

        int				flags;
        struct pollfd	sockets[SOMAXCONN]; //listening socket is sockets[0]
        int             socket_number;
        int             events_number;
        void			init_server();
        std::vector<pollfd>::iterator   new_connection();
        std::vector<pollfd>::iterator   disconnect(int fd);
        std::vector<Channel>    Channels;
        std::vector<Client>     Clients;
	
    public:
        class SocketException : public std::exception
        {
            private:
                const char  *msg;
            public:
                SocketException(const char *msg) : msg(msg) {}
                virtual const char* what() const throw()
                {
                    return msg;
                }
        };
        Server();
        ~Server();
        Server &operator=(Server const &a);
        Server(const char *port, const char *password);
        void monitoring();
        int shut_down();
        Client	*find_user_by_nickname(std::string nickname);
		void	adduser(int fd, std::string hostname);
		void    Pass(Client *client, std::vector<std::string> args);
		void	Nick(Client *client, std::vector<std::string> args);
		void	Privmsg(Client *client, std::vector<std::string> args);

		void	sig_handler(int);
        std::vector<pollfd>::iterator handle_data(std::vector<pollfd>::iterator it);
        void    errorin(bool err, const char *msg);
        Client      *find_client(std::string nickname);
        Channel     *find_channel(std::string channel_name);
};

#endif