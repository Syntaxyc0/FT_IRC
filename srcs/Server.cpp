#include "Server.hpp"

int exit_state = 0;

void Server::errorin(bool err, const char *msg)
{
    if (err == true)
        throw SocketException(msg);
}


Server::Server():_port(""), _password("")
{
    errorin(std::atoi(_port) <= 0, "Invalid port.");
}

int Server::shut_down()
{
    if (exit_state)
        return (1);
    return (0);
}

std::vector<pollfd>::iterator Server::handle_data(std::vector<pollfd>::iterator it)
{
	char buffer[1024];
	int bytes_received = recv(it->fd , buffer, sizeof(buffer), 0);
	buffer[bytes_received] = '\0';
	std::string			tmp_buffer(buffer);
	std::stringstream	ss(tmp_buffer);
	std::string line;
	while (std::getline(ss, line))
	{
		std::vector<std::string>	received = parse(line);
		if (!received.empty())
		{
			if (!strcmp("USER", received[0].c_str()))
				user(_clientList[it->fd], received);
			else if (!strcmp("PASS", received[0].c_str()))
				Pass(_clientList[it->fd], received);
			else if (!strcmp("QUIT", received[0].c_str()))
				_clientList[it->fd]->set_register(4);
			else if (!strcmp("NICK", received[0].c_str()))
				Nick(_clientList[it->fd], received);
			else if (!strcmp("PRIVMSG", received[0].c_str()))
				Privmsg(_clientList[it->fd], received);
			
		}
	}
	// std::cout<<BLUE<<"NICK : "<<_clientList[it->fd]->get_nickname()<<END<<std::endl;
	// std::cout<<CYAN<<"USERNAME : "<<_clientList[it->fd]->get_username() <<END<<std::endl;
	// std::cout<<YELLOW<<"REALNAME : "<<_clientList[it->fd]->get_realname() <<END<<std::endl;
	// std::string clean_recept(buffer);
	// clean_recept.erase(clean_recept.size() - 1);
	// std::cout <<GREEN<<"full received buffer :\n"<< buffer <<"from "<< _clientList[it->fd]->get_nickname()<<END<<std::endl;
	// std::cout <<GREEN<<"full received buffer :\n"<< clean_recept<<"from "<< _clientList[it->fd]->get_nickname()<<END<<std::endl;
	// std::cout<<std::endl;
	return (it);
}

void Server::monitoring()
{
	errorin(poll(&(*_sockets.begin()), _sockets.size(), 1000) == -1, " Failed poll() execution.\n");
	for (std::vector<pollfd>::iterator it = _sockets.begin(); it != _sockets.end(); it++)
	{
		// std::cout<<GREEN<<"size "<< _sockets.size()<<" fd "<< it->fd<<" revents "<<it->revents<<END<<std::endl;
		short revents = it->revents;
		it->revents = 0;
		if (revents & POLLHUP || revents & POLLERR) //deco de _clienList[it->fd]
		{
			if (revents & POLLERR)
				std::cerr << RED << "/!\\ Warning: An error occurred on a file descriptor." << END << std::endl;
			it = disconnect(it->fd);
		}
		else if (revents & POLLIN) //nouvelle requete
		{
			if (it->fd == _sockets.begin()->fd) //nouvelle connexion
				it = new_connection();
			else
			{
				it = handle_data(it);
				if (_clientList[it->fd]->get_registered() == 0) // faire la distinction entre une deco via quit et via une non authentification
				{
					it = disconnect(it->fd);
				}
				else if (_clientList[it->fd]->get_registered() == 4)
				{
					it = disconnect(it->fd);
				}
			}
		}
		sleep(1);
	}
}


std::vector<pollfd>::iterator Server::new_connection()
{
	char tmp_hostname[NI_MAXHOST];
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
	int fd = accept(_listening_socket, (sockaddr *)&client_addr, &client_addr_len);
    errorin(fd == -1, "Failed to accept incoming connection.\n");
	pollfd	new_poll = {fd, POLLIN, 0};
	_sockets.push_back(new_poll);
	getnameinfo((sockaddr *) &client_addr, sizeof(client_addr), tmp_hostname, NI_MAXHOST, NULL, 0, 0); //tout ca pour choper son hostname.. Ils sont fou ces romains!
	adduser(fd, tmp_hostname);
    std::cout << MAGENTA << "New connection successfull!" << END << std::endl;
	return _sockets.begin();
}

void Server::init_server()
{
    _listening_socket = socket(AF_INET, SOCK_STREAM, 0);//listen socket
    errorin(_listening_socket == -1, strerror(errno));
    int flags = fcntl(_listening_socket, F_GETFL);
	int optval = 1;
	setsockopt(_listening_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));
    fcntl(_listening_socket, F_SETFL, flags | O_NONBLOCK);//non blocking flags set
	struct	sockaddr_in	serv = {};
    std::memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(atoi(_port));
	serv.sin_addr.s_addr = INADDR_ANY; // permet de se bind a n'importe quelle IP
    errorin(bind(_listening_socket, (struct sockaddr *)&serv, sizeof(serv))  == -1, "Failed to bind listen socket.");
    errorin(listen(_listening_socket, SOMAXCONN) == -1, "Failed to listen on socket.");
	pollfd	first_socket = {_listening_socket, POLLIN, 0};
	_sockets.push_back(first_socket);
}

Server::Server(const char *port, const char *password): _port(port), _password(password)
{
    errorin(std::atoi(_port) <= 0, "Invalid port.\n");
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
            if (close(it->fd))
                std::cerr << RED << "/!\\ Error while closing file descriptor: " << strerror(errno) << END << std::endl;
            it->fd = 0;
        }
    }
	exit_state = 1;
    std::cout << "\n\t-- Server shutted down successfully --" << std::endl; 
}

void	Server::adduser(int fd, std::string hostname)
{
	Client *newuser = new	Client(fd, hostname);
	_clientList.insert(std::make_pair(fd, newuser));
	std::cout<<GREEN<<"New user added"<<" fd : "<<fd<<" hostname "<<hostname<<END<<std::endl;	//DEBUG
}

std::vector<pollfd>::iterator Server::disconnect(int fd)
{

	//TODO: lui faire quitter son channel actif s'il en a un
	for (std::vector<pollfd>::iterator it =_sockets.begin(); it != _sockets.end(); it++)
	{
		if (it->fd == fd)
		{
			std::cout << MAGENTA << _clientList[it->fd]->get_username() << " has disconnected" << END << std::endl;
			_sockets.erase(it);
			delete(_clientList[fd]);
			_clientList.erase(fd);
			close(fd);
			return _sockets.begin();
		}	
	}
	return _sockets.begin();
}

//****************************************************//
//              Channel/Client Function               //
//****************************************************//

Client  *Server::find_client(std::string nickname)
{
    for ( int i = 0; i < (int)Clients.size(); i++ )
        if ( nickname == Clients.at(i).get_nickname() )
            return ( &Clients.at(i) );
    return (0);
}

Channel *Server::find_channel(std::string channel_name)
{
    for ( int i = 0; i < (int)Channels.size(); i++ )
        if ( channel_name == Channels.at(i).get_name() )
            return ( &Channels.at(i) );
    return (0);
}