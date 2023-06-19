#include "Commands.hpp"

void	Topic(Client *client, std::vector<std::string> args, Server &server)
{
	Channel *chan;

	if (args.size() < 2)
	{
		client->send_reply(ERR_NEEDMOREPARAMS(client->get_hostname(), "TOPIC"));
		return ;
	}
	std::cout<<"args "<<args[1].erase(0, 1)<<std::endl;
	chan = server.find_channel("#" + args[1]);
	if (!chan)
	{
		std::cout<<BLUE<<"nope "<<END<<std::endl;
		return ;
	}
	if (args.size() == 2)
	{
		if (server.find_channel(args[1])->get_topic() == "")
			client->send_message( ":localhost 331 "+ client->get_nickname() + " " + args[1] + " :" + "No topic is set" );
		else
			client->send_message( ":localhost 332 "+ client->get_nickname() + " " + args[1] + " :" + chan->get_topic() );
	}
	else
	{
		if (chan->get_restriction_TOPIC_cmd() && !chan->is_operator(client->get_nickname()))
			client->send_reply(ERR_CHANOPRIVSNEEDED(client->get_nickname(), chan->get_name()));
		else
		{
			chan->set_topic(args[2]);
			chan->send_all( ":localhost 332 "+ client->get_nickname() + " " + args[1] + " :" + args[2] );
		}
	}

}