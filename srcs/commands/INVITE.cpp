//****************************************************//
//                  Commande INVITE                   //
//****************************************************//

#include "Commands.hpp"

// "/INVITE [user.nickname]" Invite un client sur le channel de l'utilisateur.
// Erreur si : le client n'existe pas, l'utilisateur n'est pas dams un channel ,si il n'est pas opérateur de cette channel ou
// le client invité est déjà sur le channel.
// Un message s'affichera si la commande s'execute avec succès.

void	Invite( Client *client, std::vector<std::string> received, Server &server )
{
	if ( invite_error( client, received, server) )
		return;

	Channel* channel = server.find_channel( received[2] );
	Client *target = server.find_client( received[1] );
	std::string target_nick = target->get_nickname();

	// Reply from user command
	client->send_reply( RPL_INVITING( client->get_nickname(), target_nick, channel->get_name() ) );
	client->send_message( client->get_nickname() + " INVITE " + target_nick + " " + channel->get_name() );

	// add client to channel
	channel->add_client( received[1] );
	client->set_add_channel( channel );

	//message
	channel->send_all( target->get_nickname() + " has joined " + received[2] );
	if ( channel->get_topic().size() )
		client->send_reply( RPL_TOPIC(target_nick, channel->get_name(), channel->get_topic() ) );
	target->send_reply( "353 " + target_nick + " = " + received[2] + " :" + channel_list_user( received[2], server ) );
	target->send_reply( "366 " + target_nick + " " + received[2] + " :End of NAMES list" );
}

bool	invite_error( Client *client, std::vector<std::string> received, Server &server )
{
	Channel* channel = server.find_channel( received[2] );
	std::string channel_name = channel->get_name();
	std::string nickname = client->get_nickname();

	if ( received.size() != 3 )
		return ( client->send_reply( ERR_NEEDMOREPARAMS( nickname, "INVITE" ) ), true );

	else if ( !channel )
		return ( client->send_reply( ERR_NOSUCHCHANNEL( nickname, channel_name ) ), true );

	else if ( !channel->is_channelClient( nickname ) )
		return ( client->send_reply( ERR_NOTONCHANNEL( nickname, channel_name ) ), true );

	else if ( !channel->is_operator( nickname ) )
		return ( client->send_reply( ERR_CHANOPRIVSNEEDED( nickname, channel_name ) ), true );

	else if ( channel->is_channelClient( server.find_client( received[1] )->get_nickname() ) )
		return ( client->send_reply( ERR_USERONCHANNEL( nickname, server.find_client( received[1] )->get_nickname(),  channel_name ) ), true );

	else if ( channel->get_user_limit() && (int)channel->get_channelClients().size() >= channel->get_user_limit_nb() )
		return ( client->send_reply( ERR_CHANNELISFULL( client->get_nickname(), channel_name ) ), true );

	return ( false );
}
