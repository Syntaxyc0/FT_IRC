//****************************************************//
//                  Commande INVITE                   //
//****************************************************//

#include "Commands.hpp"

// "/INVITE [user.nickname]" Invite un client sur le channel de l'utilisateur.
// Erreur si : le client n'existe pas, l'utilisateur n'est pas dams un channel ,si il n'est pas opérateur de cette channel ou
// le client invité est déjà sur le channel.
// Un message s'affichera si la commande s'execute avec succès.

void	invite_command(Client *client, std::vector<std::string> received, Server &server);
{
	if (invite_error(current, me, target))
		return;

	// add client to channel's list
	current.add_client( target );

	// add channel to client's _current_channel 
	current.get_server()->find_client( target )->set_current_channel( current.get_name() );

	std::string message = target;
	message.append( " is now on " );
	message.append( current.get_name() );
	me.send_reply( message );
}

bool	invite_error( Channel &current, Client &me, std::string target )
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
