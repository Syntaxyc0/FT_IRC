#include "Commands.hpp"

void	Quit( Client *client, std::vector<std::string> args, Server &serv )
{
	(void)	serv;
	(void)	args;
	std::string reason = "";
	if (args.size() != 1)
	{
		for (unsigned int i = 1; i < args.size() ; i++)
		{
			reason += args[i];
			if (i != args.size() - 1)
				reason += " ";
		}
	}
	quit_channels( client, args, serv );
	serv.broadcast_server(":" + client->get_fullname() + " QUIT :" + reason);
	client->set_register(DISCONNECTED);
}

void	quit_channels( Client *client, std::vector<std::string> args, Server &serv )
{
	std::vector<std::string> channel_list = client->get_channelList();

	for ( int i = 0; i < (int)channel_list.size(); i++ )
	{	
		Channel *channel = serv.find_channel( channel_list[i] );
		std::vector<std::string> operators = channel->get_operators();

		if ( client->get_nickname() == channel_list[i] )
			operators.erase( operators.begin() + channel->find_operator_index( client->get_nickname() ) ) ;
			
	}
}