#include "Server.hpp"

Server::Server():_port(""), _password("")
{
    errorin(std::atoi(_port) <= 0, "Invalid port.");
}

int Server::shut_down()
{
    if (_exit)
        return (1);
    return (0);
}

void Server::monitoring()
{
	if (poll(&(*_sockets.begin()), _sockets.size(), 1000) == -1)
	{
		std::cerr << " Failed poll() execution.\n";
        return;
	}
	for (std::vector<pollfd>::iterator it = _sockets.begin(); it != _sockets.end(); it++)
	{
		std::cout<<GREEN<<"size "<< _sockets.size()<<" fd "<< it->fd<<" revents "<<it->revents<<END<<std::endl;
		if (it->revents == POLLERR)
			std::cerr << "/!\\ Warning: An error occurred on a file descriptor.\n";
		else if (it->revents == POLLHUP) //deco de _clienList[it->fd]
		{
			disconnect(it->fd);
			break ;
		}
		else if (it->revents == POLLIN) //nouvelle requete
		{
			if (it->fd == _sockets.begin()->fd) //nouvelle connexion
			{
				new_connection();
				break ;
			}
			else //handle message function needed, below is just a snippet
			{
				char buffer[1024];
				int bytes_received = recv(it->fd , buffer, sizeof(buffer), 0);
				buffer[bytes_received] = '\0';
				std::string	to_parse(buffer);
				std::vector<std::string>	received = parse(buffer);
				if (!received.empty())
				{
					if (!strcmp("userhost", received[0].c_str()))
					{
						user(_clientList[it->fd], received);
					}
					// else if (!strcmp("PASS", received[0].c_str()))
					// {
					// 	Pass(_clientList[it->fd], received);
					// }
					else if (!strcmp("QUIT", received[0].c_str()))
					{
						disconnect(it->fd);
						break ;
					}
					else if (!strcmp("NICK", received[0].c_str()))
					{
						std::stringstream ss;
						ss << _clientList[it->fd]->get_registered();
						std::string tmp = ss.str();
						_clientList[it->fd]->send_reply(tmp);
						nick(_clientList[it->fd], received);
					}
				}
				std::cout <<GREEN<<"received "<< to_parse<<"from "<< _clientList[it->fd]->get_nickname()<<END<<std::endl;
			}
		}
		sleep(1);
	}
}

int Server::new_connection()
{
	char tmp_hostname[NI_MAXHOST];
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
	int fd = 0;
    fd = accept(_listening_socket, (sockaddr *)&client_addr, &client_addr_len);
    if (fd == -1)
    {
        std::cerr << "Failed to accept incoming connection.\n";
        return (-1);
    }
	pollfd	new_poll = {fd, POLLIN, 0};
	_sockets.push_back(new_poll);
	getnameinfo((sockaddr *) &client_addr, sizeof(client_addr), tmp_hostname, NI_MAXHOST, NULL, 0, 0); //tout ca pour choper son hostname..
	adduser(&fd, tmp_hostname);
    std::cout << "New connection successfull!\n";
    return (0);
}

void Server::init_server()
{
    _listening_socket = socket(AF_INET, SOCK_STREAM, 0);//listen socket
    errorin(_listening_socket == -1, strerror(errno));
    int flags = fcntl(_listening_socket, F_GETFL);
	int optval = 1;
	setsockopt(_listening_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)); // permet de reutiliser cette socket, besoin que de deux on a qu'un thread
    fcntl(_listening_socket, F_SETFL, flags | O_NONBLOCK);//non blocking flags set
	struct	sockaddr_in	serv = {};
    std::memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(atoi(_port));
	serv.sin_addr.s_addr = INADDR_ANY; // permet de se bind a n'importe quelle IP
    if(bind(_listening_socket, (struct sockaddr *)&serv, sizeof(serv))  == -1)
        errorin(1, "Failed to bind listen socket.");
    errorin(listen(_listening_socket, SOMAXCONN) == -1, "Failed to listen on socket.");
	pollfd	first_socket = {_listening_socket, POLLIN, 0};
	_sockets.push_back(first_socket);
    std::cout << "Listening on port " << _port << "..." << std::endl;
}

Server::Server(const char *port, const char *password): _port(port), _password(password)
{
    errorin(std::atoi(_port) <= 0, "Invalid port.\n");
    _exit = 0;
    init_server();
}

Server::~Server()
{
	if (!_clientList.empty())
	{
		for (std::map<int, Client*>::iterator it = _clientList.begin(); it != _clientList.end(); it++)
			delete(it->second);
	}
    fcntl(_listening_socket, F_SETFL, O_RDONLY);
    for (std::vector<pollfd>::iterator it = _sockets.begin(); it != _sockets.end(); it++)
    {
        if (it->fd)
        {
            char buffer[1024];
            while (recv(it->fd, buffer, sizeof(buffer), 0) > 0) {}
            if (close(it->fd))
                std::cerr << "/!\\ Error while closing file descriptor: " << strerror(errno) << std::endl;
            it->fd = 0;
        }
    }
    if (close(_listening_socket))
        std::cerr << "/!\\ Error while closing file descriptor: " << strerror(errno) << std::endl;
    std::cout << "Server shutted down successfully" << std::endl; 
}

void	Server::adduser(int *fd, std::string hostname)
{
	Client *newuser = new	Client(*fd, hostname);
	_clientList.insert(std::make_pair(*fd, newuser));
	std::cout<<GREEN<<"New user added"<<" fd : "<<*fd<<" hostname "<<hostname<<END<<std::endl;	//DEBUG
	newuser->send_reply(RPL_WELCOME(newuser->get_nickname(), newuser->get_username(), hostname));
}

void	Server::disconnect(int fd)
{

	//TODO: lui faire quitter son channel actif s'il en a un
	_clientList.erase(fd);
	for (std::vector<pollfd>::iterator it =_sockets.begin(); it != _sockets.end(); it++)
	{
		if (it->fd == fd)
		{
			_sockets.erase(it);
			close(fd);
			return ;
		}	
	}
}