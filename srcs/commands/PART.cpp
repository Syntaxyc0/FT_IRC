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

			// if ( channel->is_primordial( client->get_nickname() ) )
			// 	heritance( args, serv, i );

			if ( !channel->get_channelClients().size() )
				serv.del_channel( channel->get_name() );

			// std::cout<< ":" + client->get_fullname() + " PART " + args[i] <<std::endl;
			client->send_message(":" + client->get_fullname() + " PART " + args[i] + " .");
			channel->send_all(":" + client->get_fullname() + " PART " + args[i] + " .");
		}
	}
}

void	heritance( std::vector<std::string> args, Server &serv, int index )
{
	Channel *channel = serv.find_channel( args[index] );

	if ( channel->get_operators().size() )
	{
		channel->set_primo( channel->get_operators()[0] );
		channel->send_all( channel->get_operators()[0] + " is the new Primordial" );
	}
	else if ( channel->get_channelClients().size() )
	{
		channel->set_primo( channel->get_channelClients()[0] );
		channel->add_operator( channel->get_channelClients()[0] );
		channel->send_all( channel->get_channelClients()[0] + " is the new Primordial" );
	}
}