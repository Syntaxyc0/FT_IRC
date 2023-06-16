//****************************************************//
//                  Commande INVITE                   //
//****************************************************//

#include "Commands.hpp"

// "/INVITE [user.nickname]" Invite un client sur le channel de l'utilisateur.
// Erreur si : le client n'existe pas, l'utilisateur n'est pas dams un channel ,si il n'est pas opérateur de cette channel ou
// le client invité est déjà sur le channel.
// Un message s'affichera si la commande s'execute avec succès.

void	invite_command( Client *client, std::vector<std::string> received, Server &server );
{
	if ( invite_error( client ) )
		return;

	// add client to channel's list
	current.add_client( received[1] );

	me.send_message( "PRIVMSG " + server.find_channel( received[2] ) + " :" + server.find_client( received[1] ).get_nickname() + " has joined channel" );
}

bool	invite_error( Client *client, std::vector<std::string> received, Server &server )
{
	if ( !current.get_server()->find_client( target ) )
		return ( me.send_reply( ERR_NOSUCHCHANNEL( me.get_nickname(), current.get_name() ) ), true );

	else if ( !me.get_current_channel().size() )
		return ( me.send_reply( ERR_NOTONCHANNEL( me.get_nickname(), current.get_name() ) ), true );

	else if ( !current.is_operator( me.get_nickname() ) )
		return ( me.send_reply( ERR_CHANOPRIVSNEEDED( me.get_nickname(), current.get_name() ) ), true );

	else if ( current.is_channelClient( target ) )
		return ( me.send_reply( ERR_USERONCHANNEL( me.get_nickname(), target,  current.get_name() ) ), true );

	else if ( (int)current.get_channelClients().size() >= current.get_user_limit_nb() )
		return ( me.send_reply( ERR_LIMITREACHED( current.get_name() ) ), true );

	return ( false )
}
