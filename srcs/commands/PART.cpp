#include "Channel.hpp"
#include "Commands.hpp"
#include "Server.hpp"

// window close handling
void	Part(Client *client, std::vector<std::string> args, Server &serv)
{
	Channel *channel = 0;
	for (unsigned long i = 1; i < args.size(); i++)
	{
		channel = serv.find_channel( args[i] );
		if ( !channel )
		{
			client->send_message( ERR_NOSUCHCHANNEL( client->get_nickname(), args[i] ) );
			continue ;
		}
		else if ( ( channel && channel->find_client_index( client->get_nickname() ) == -1 ) )
		{
			client->send_message( ERR_NOTONCHANNEL(client->get_nickname(), args[i] ) );
			continue ;
		}
		else
		{
			channel->kick_client( client->get_nickname() );
			// std::cout<< ":" + client->get_fullname() + " PART " + args[i] <<std::endl;
			client->send_message(":" + client->get_fullname() + " PART " + args[i] + " .");
			channel->send_all(":" + client->get_fullname() + " PART " + args[i] + " .");
		}
	}
}